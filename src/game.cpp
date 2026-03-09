#include "game.h"
#include <iostream>
#include <memory>
#include <cmath>
#include <fstream>
#include <sstream>
#include "SDL.h"
#include "collision_detection.h"

Game::Game(std::size_t screen_width, std::size_t screen_height) : 
      screen_width(screen_width),
      screen_height(screen_height) {
    
    Reset();
}

void Game::Reset() {
    LoadGeometryConfig("../data/geometry.txt");
    BuildEnvironment();
    car.speed = 0.0f;
    car.steering_angle = 0.0f;
    car.color = {0, 122, 204, 255};
}

void Game::LoadGeometryConfig(std::string path) {
  std::ifstream file(path);
  if (!file.is_open()) {
    std::cerr << "Could not open config file: " << path << ". Using defaults.\n";
    return;
  }
  std::string line;
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') continue;
    std::istringstream iss(line);
    std::string key;
    float value;
    if (!(iss >> key >> value)) continue;
    if (key == "driveway_width") config.driveway_width = value;
    else if (key == "driveway_top_width") config.driveway_top_width = value;
    else if (key == "driveway_depth") config.driveway_depth = value;
    else if (key == "carport_door_width") config.carport_door_width = value;
    else if (key == "carport_inside_width") config.carport_inside_width = value;
    else if (key == "carport_inside_depth") config.carport_inside_depth = value;
    else if (key == "alley_width") config.alley_width = value;
    else if (key == "carport_x_offset") config.carport_x_offset = value;
    else if (key == "driveway_x_offset") config.driveway_x_offset = value;
    else if (key == "car_start_x") config.car_start_x = value;
    else if (key == "car_start_y_offset") config.car_start_y_offset = value;
    else if (key == "car_start_facing_right") config.car_start_facing_right = value;
  }
  std::cout << "Geometry Loaded and Simulation Reset.\n";
}

void Game::BuildEnvironment() {
    obstacles.clear();
    // Scale: 10 pixels = 1 foot.
    
    // PRIMARY VERTICAL ANCHOR (Boundary between Alley and Driveway)
    float baseline_y = 440.0f;
    
    // PRIMARY HORIZONTAL ANCHOR (Center of Carport, shifted by offset)
    float center_x = 400.0f + (config.carport_x_offset * 10.0f);

    // 1. ALLEYWAY
    float alley_width_px = config.alley_width * 10.0f;
    float alley_bottom_y = baseline_y + alley_width_px;
    float alley_center_y = baseline_y + (alley_width_px / 2.0f);
    
    // Position car based on config
    float start_x_px = config.car_start_x * 10.0f;
    float start_y_px = alley_center_y + (config.car_start_y_offset * 10.0f);
    float start_yaw = (config.car_start_facing_right > 0.5f) ? 0.0f : 180.0f;
    car.setPose(start_x_px, start_y_px, start_yaw);

    // Bottom alley wall (outside alley)
    auto wall_bottom = std::make_unique<GameObject>();
    wall_bottom->setPose(screen_width / 2.0f, alley_bottom_y + kWallThickness / 2.0f, 0);
    wall_bottom->setWidth(screen_width);
    wall_bottom->setHeight(kWallThickness);
    wall_bottom->use_color = true;
    wall_bottom->color = {100, 100, 100, 255};
    obstacles.push_back(std::move(wall_bottom));

    // 2. DOOR X-DIMENSIONS
    float door_width_px = config.carport_door_width * 10.0f;
    float door_left_x = center_x - (door_width_px / 2.0f);
    float door_right_x = center_x + (door_width_px / 2.0f);

    // 3. DRIVEWAY X-DIMENSIONS (Anchored to Door Left Edge + offset)
    float dw_left_x = door_left_x + (config.driveway_x_offset * 10.0f); 
    float dw_width_px = config.driveway_width * 10.0f;
    float dw_right_x = dw_left_x + dw_width_px;
    float dw_center_x = (dw_left_x + dw_right_x) / 2.0f;

    // Alley top walls (Gap for driveway, outside alley and driveway)
    auto wall_top_l = std::make_unique<GameObject>();
    float w_l = std::max(0.0f, dw_left_x);
    wall_top_l->setPose(w_l / 2.0f, baseline_y - kWallThickness / 2.0f, 0); 
    wall_top_l->setWidth(w_l); 
    wall_top_l->setHeight(kWallThickness);
    wall_top_l->use_color = true;
    wall_top_l->color = {100, 100, 100, 255};
    obstacles.push_back(std::move(wall_top_l));

    auto wall_top_r = std::make_unique<GameObject>();
    float w_r = std::max(0.0f, (float)screen_width - dw_right_x);
    wall_top_r->setPose(dw_right_x + w_r / 2.0f, baseline_y - kWallThickness / 2.0f, 0); 
    wall_top_r->setWidth(w_r); 
    wall_top_r->setHeight(kWallThickness);
    wall_top_r->use_color = true;
    wall_top_r->color = {100, 100, 100, 255};
    obstacles.push_back(std::move(wall_top_r));

    // 4. DRIVEWAY Y-DIMENSIONS
    float dw_depth_px = config.driveway_depth * 10.0f;
    float dw_top_y = baseline_y - dw_depth_px;
    float dw_top_width_px = config.driveway_top_width * 10.0f;
    
    // Left side is vertical
    float dw_top_left_x = dw_left_x;
    // Right side is tapered
    float dw_top_right_x = dw_left_x + dw_top_width_px;
    
    // Visual indicator of driveway (clear space)
    auto driveway = std::make_unique<GameObject>();
    driveway->setPose(dw_left_x, baseline_y, 0); 
    // Define trapezoid vertices relative to (dw_left_x, baseline_y)
    // Bottom-Left, Bottom-Right, Top-Right, Top-Left
    driveway->setVertices({
        {0, 0},
        {dw_width_px, 0},
        {dw_top_right_x - dw_left_x, -dw_depth_px},
        {0, -dw_depth_px}
    });
    driveway->use_color = true;
    driveway->color = {80, 80, 80, 255}; 
    driveway->setImageName("driveway_shaded"); 
    obstacles.insert(obstacles.begin(), std::move(driveway));

    // Driveway side walls
    // Left side wall (Exactly vertical)
    auto wall_dw_l = std::make_unique<GameObject>();
    wall_dw_l->setPose(dw_left_x - kWallThickness / 2.0f, (baseline_y + dw_top_y) / 2.0f, -90);
    wall_dw_l->setWidth(dw_depth_px);
    wall_dw_l->setHeight(kWallThickness);
    wall_dw_l->use_color = true;
    wall_dw_l->color = {120, 120, 120, 255};
    obstacles.push_back(std::move(wall_dw_l));

    // Right side wall (Tapered)
    float dx_r = dw_top_right_x - dw_right_x;
    float dy = dw_top_y - baseline_y;
    float length_r = std::sqrt(dx_r * dx_r + dy * dy);
    float angle_r = std::atan2(dy, dx_r) * 180.0f / M_PI;

    auto wall_dw_r = std::make_unique<GameObject>();
    float perp_angle_r = (angle_r + 90.0f) * M_PI / 180.0f;
    float offset_x_r = (kWallThickness / 2.0f) * std::cos(perp_angle_r);
    float offset_y_r = (kWallThickness / 2.0f) * std::sin(perp_angle_r);

    wall_dw_r->setPose((dw_right_x + dw_top_right_x) / 2.0f + offset_x_r, 
                       (baseline_y + dw_top_y) / 2.0f + offset_y_r, 
                       angle_r);
    wall_dw_r->setWidth(length_r);
    wall_dw_r->setHeight(kWallThickness);
    wall_dw_r->use_color = true;
    wall_dw_r->color = {120, 120, 120, 255};
    obstacles.push_back(std::move(wall_dw_r));

    // 5. CARPORT ASSEMBLY
    
    // Top driveway boundary walls (connecting tapered driveway side tops to carport posts)
    if (door_left_x > dw_top_left_x) {
        auto wall_dw_tl = std::make_unique<GameObject>();
        float w = door_left_x - dw_top_left_x;
        wall_dw_tl->setPose(dw_top_left_x + w / 2.0f, dw_top_y - kWallThickness / 2.0f, 0);
        wall_dw_tl->setWidth(w);
        wall_dw_tl->setHeight(kWallThickness);
        wall_dw_tl->use_color = true;
        wall_dw_tl->color = {120, 120, 120, 255};
        obstacles.push_back(std::move(wall_dw_tl));
    }
    if (dw_top_right_x > door_right_x) {
        auto wall_dw_tr = std::make_unique<GameObject>();
        float w = dw_top_right_x - door_right_x;
        wall_dw_tr->setPose(door_right_x + w / 2.0f, dw_top_y - kWallThickness / 2.0f, 0); 
        wall_dw_tr->setWidth(w);
        wall_dw_tr->setHeight(kWallThickness);
        wall_dw_tr->use_color = true;
        wall_dw_tr->color = {120, 120, 120, 255};
        obstacles.push_back(std::move(wall_dw_tr));
    }

    // Carport door posts (outside entrance clear space)
    auto post_l = std::make_unique<GameObject>();
    post_l->setPose(door_left_x - kPostSize / 2.0f, dw_top_y - kPostSize / 2.0f, 0); 
    post_l->setWidth(kPostSize);
    post_l->setHeight(kPostSize);
    post_l->use_color = true;
    post_l->color = {255, 165, 0, 255}; 
    obstacles.push_back(std::move(post_l));

    auto post_r = std::make_unique<GameObject>();
    post_r->setPose(door_right_x + kPostSize / 2.0f, dw_top_y - kPostSize / 2.0f, 0); 
    post_r->setWidth(kPostSize);
    post_r->setHeight(kPostSize);
    post_r->use_color = true;
    post_r->color = {255, 165, 0, 255};
    obstacles.push_back(std::move(post_r));

    // Carport interior (clear space width and depth)
    float in_width_px = config.carport_inside_width * 10.0f;
    float in_depth_px = config.carport_inside_depth * 10.0f;
    float in_left_x = center_x - in_width_px / 2.0f;
    float in_right_x = center_x + in_width_px / 2.0f;
    float in_back_y = dw_top_y - in_depth_px;
    float in_center_y = (dw_top_y + in_back_y) / 2.0f;

    auto wall_int_l = std::make_unique<GameObject>();
    wall_int_l->setPose(in_left_x - kWallThickness / 2.0f, in_center_y, 0);
    wall_int_l->setWidth(kWallThickness);
    wall_int_l->setHeight(in_depth_px); 
    wall_int_l->use_color = true;
    wall_int_l->color = {150, 150, 150, 255};
    obstacles.push_back(std::move(wall_int_l));

    auto wall_int_r = std::make_unique<GameObject>();
    wall_int_r->setPose(in_right_x + kWallThickness / 2.0f, in_center_y, 0);
    wall_int_r->setWidth(kWallThickness);
    wall_int_r->setHeight(in_depth_px);
    wall_int_r->use_color = true;
    wall_int_r->color = {150, 150, 150, 255};
    obstacles.push_back(std::move(wall_int_r));
    
    // Back wall (outside interior depth)
    auto wall_back = std::make_unique<GameObject>();
    wall_back->setPose(center_x, in_back_y - kWallThickness / 2.0f, 0);
    wall_back->setWidth(in_width_px);
    wall_back->setHeight(kWallThickness);
    wall_back->use_color = true;
    wall_back->color = {150, 150, 150, 255};
    obstacles.push_back(std::move(wall_back));

    // Parking target
    auto target = std::make_unique<GameObject>();
    target->setPose(center_x, in_back_y + 81.0f, -90.0);
    target->setWidth(162);
    target->setHeight(66);
    target->use_color = true;
    target->color = {0, 255, 0, 50}; 
    target->setImageName("target");
    obstacles.insert(obstacles.begin(), std::move(target));
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    controller.HandleInput(running, car, *this);
    Update();
    renderer.Render(car, obstacles, measure_p1.x, measure_p1.y, measure_p2.x, measure_p2.y, mouse_pos.x, mouse_pos.y);

    frame_end = SDL_GetTicks();
    frame_count++;
    frame_duration = frame_end - frame_start;

    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(car.getSteeringAngleDeg(), frame_count, measure_mode, current_measure_ft);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  if (measure_p1.x != -1 && measure_p2.x != -1) {
    float dx = (float)(measure_p2.x - measure_p1.x);
    float dy = (float)(measure_p2.y - measure_p1.y);
    current_measure_ft = std::sqrt(dx * dx + dy * dy) / 10.0f;
  }

  auto previous_pose = car.getPose();
  car.Update();

  bool collision = false;
  for (auto const &obstacle : obstacles) {
    if (obstacle->getImageName() == "target" || 
        obstacle->getImageName() == "driveway_shaded") continue; 
    if (CollisionDetection::detect_collision(car, *obstacle)) {
      collision = true;
      break;
    }
  }

  if (collision) {
    car.setPose(previous_pose.x, previous_pose.y, previous_pose.yaw);
    car.use_color = true;
    car.color = {255, 0, 0, 255}; 
    car.speed = 0;
  } else {
    car.use_color = true;
    car.color = {0, 122, 204, 255}; 
  }
}
