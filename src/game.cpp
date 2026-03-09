#include "game.h"
#include <iostream>
#include <memory>
#include "SDL.h"
#include "collision_detection.h"

Game::Game(std::size_t screen_width, std::size_t screen_height) : 
      screen_width(screen_width),
      screen_height(screen_height) {
    
    // Scale: 10 pixels = 1 foot.
    // Car starts on the right side of the alley, facing Left (yaw = 180.0)
    car.setPose(700, 500, 180.0);

    // Alley bottom wall (12.5ft wide alley)
    auto wall_bottom = std::make_unique<GameObject>();
    wall_bottom->setPose(screen_width/2.0f, 565, 0);
    wall_bottom->setWidth(screen_width);
    wall_bottom->setHeight(10);
    wall_bottom->use_color = true;
    wall_bottom->color = {100, 100, 100, 255};
    obstacles.push_back(std::move(wall_bottom));

    float alley_top_y = 440.0;
    
    // Driveway is 25.95ft wide (259.5 px).
    // Left boundary shifted left by 1ft (10px) from the door post (at 350).
    // New left edge = 340.
    // New right edge = 340 + 259.5 = 599.5.
    float dw_left_x = 340.0;
    float dw_right_x = 599.5;
    float dw_width = 259.5;
    float dw_center_x = (dw_left_x + dw_right_x) / 2.0f;

    // Alley top wall with 25.95ft gap from dw_left_x to dw_right_x
    auto wall_top_l = std::make_unique<GameObject>();
    wall_top_l->setPose(dw_left_x / 2.0f, alley_top_y, 0);
    wall_top_l->setWidth(dw_left_x); 
    wall_top_l->setHeight(10);
    wall_top_l->use_color = true;
    wall_top_l->color = {100, 100, 100, 255};
    obstacles.push_back(std::move(wall_top_l));

    auto wall_top_r = std::make_unique<GameObject>();
    float wall_r_width = screen_width - dw_right_x;
    wall_top_r->setPose(dw_right_x + wall_r_width / 2.0f, alley_top_y, 0); 
    wall_top_r->setWidth(wall_r_width); 
    wall_top_r->setHeight(10);
    wall_top_r->use_color = true;
    wall_top_r->color = {100, 100, 100, 255};
    obstacles.push_back(std::move(wall_top_r));

    // Driveway floor
    float driveway_top_y = 343.9;
    auto driveway = std::make_unique<GameObject>();
    driveway->setPose(dw_center_x, 391.95, 0); 
    driveway->setWidth(dw_width);
    driveway->setHeight(96.1);
    driveway->use_color = true;
    driveway->color = {80, 80, 80, 255}; 
    driveway->setImageName("target"); 
    obstacles.insert(obstacles.begin(), std::move(driveway));

    // Driveway side walls
    auto wall_dw_l = std::make_unique<GameObject>();
    wall_dw_l->setPose(dw_left_x - 2.5f, 391.95, 0); // Inner face at 340
    wall_dw_l->setWidth(5);
    wall_dw_l->setHeight(96.1);
    wall_dw_l->use_color = true;
    wall_dw_l->color = {120, 120, 120, 255};
    obstacles.push_back(std::move(wall_dw_l));

    auto wall_dw_r = std::make_unique<GameObject>();
    wall_dw_r->setPose(dw_right_x + 2.5f, 391.95, 0); // Inner face at 599.5
    wall_dw_r->setWidth(5);
    wall_dw_r->setHeight(96.1);
    wall_dw_r->use_color = true;
    wall_dw_r->color = {120, 120, 120, 255};
    obstacles.push_back(std::move(wall_dw_r));

    // Top driveway boundary wall
    // Connects left driveway wall (340) to left door post (350)
    auto wall_dw_tl = std::make_unique<GameObject>();
    wall_dw_tl->setPose(345, driveway_top_y, 0);
    wall_dw_tl->setWidth(10);
    wall_dw_tl->setHeight(10);
    wall_dw_tl->use_color = true;
    wall_dw_tl->color = {120, 120, 120, 255};
    obstacles.push_back(std::move(wall_dw_tl));

    // Connects right door post (450) to right driveway wall (599.5)
    // Width = 149.5. Center = 450 + 74.75 = 524.75
    auto wall_dw_tr = std::make_unique<GameObject>();
    wall_dw_tr->setPose(524.75, driveway_top_y, 0); 
    wall_dw_tr->setWidth(149.5);
    wall_dw_tr->setHeight(10);
    wall_dw_tr->use_color = true;
    wall_dw_tr->color = {120, 120, 120, 255};
    obstacles.push_back(std::move(wall_dw_tr));

    // Carport door posts
    auto post_l = std::make_unique<GameObject>();
    post_l->setPose(344, driveway_top_y, 0); // Inner edge at 350
    post_l->setWidth(12);
    post_l->setHeight(12);
    post_l->use_color = true;
    post_l->color = {255, 165, 0, 255}; 
    obstacles.push_back(std::move(post_l));

    auto post_r = std::make_unique<GameObject>();
    post_r->setPose(456, driveway_top_y, 0); // Inner edge at 450
    post_r->setWidth(12);
    post_r->setHeight(12);
    post_r->use_color = true;
    post_r->color = {255, 165, 0, 255};
    obstacles.push_back(std::move(post_r));

    // Carport interior
    float int_center_y = 217.65;
    auto wall_int_l = std::make_unique<GameObject>();
    wall_int_l->setPose(341.25, int_center_y, 0); // Inner face at 343.75
    wall_int_l->setWidth(5);
    wall_int_l->setHeight(252.5); 
    wall_int_l->use_color = true;
    wall_int_l->color = {150, 150, 150, 255};
    obstacles.push_back(std::move(wall_int_l));

    auto wall_int_r = std::make_unique<GameObject>();
    wall_int_r->setPose(458.75, int_center_y, 0); // Inner face at 456.25
    wall_int_r->setWidth(5);
    wall_int_r->setHeight(252.5);
    wall_int_r->use_color = true;
    wall_int_r->color = {150, 150, 150, 255};
    obstacles.push_back(std::move(wall_int_r));
    
    // Back wall
    auto wall_back = std::make_unique<GameObject>();
    wall_back->setPose(400, 91.4, 0);
    wall_back->setWidth(112.5);
    wall_back->setHeight(10);
    wall_back->use_color = true;
    wall_back->color = {150, 150, 150, 255};
    obstacles.push_back(std::move(wall_back));

    // Parking target
    auto target = std::make_unique<GameObject>();
    target->setPose(400, 172.4, -90.0);
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
    controller.HandleInput(running, car);
    Update();
    renderer.Render(car, obstacles);
    frame_end = SDL_GetTicks();
    frame_count++;
    frame_duration = frame_end - frame_start;
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(car.getSteeringAngleDeg(), frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  car.Update();
  bool collision = false;
  for (auto const &obstacle : obstacles) {
    if (obstacle->getImageName() == "target") continue; 
    if (CollisionDetection::detect_collision(car, *obstacle)) {
      collision = true;
      break;
    }
  }
  if (collision) {
    car.use_color = true;
    car.color = {255, 0, 0, 255}; 
    car.speed = 0;
  } else {
    car.use_color = true;
    car.color = {0, 122, 204, 255}; 
  }
}
