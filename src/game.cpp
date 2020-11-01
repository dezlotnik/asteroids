#include "game.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include "SDL.h"
#include "collision_detection.h"

Game::Game(std::size_t screen_width, std::size_t screen_height) : 
      screen_width(screen_width),
      screen_height(screen_height) {
    spaceship.setPose(screen_width/2,screen_height/2,-90.0);

    // for (size_t i = 0; i < n_asteroids; i++)
    // {
    //     asteroids.push_back(std::move(std::make_unique<Asteroid>()));
    // }

    // for (size_t i = 0; i < n_enemies; i++)
    // {
    //     enemies.push_back(std::move(std::make_unique<Enemy>()));
    // }

}

std::vector<std::vector<int>> Game::loadLevels() {
  std::ifstream filestream("../data/levels.txt");
  std::vector<std::vector<int>> level_configs;
  std::string line, key, value;
  if (filestream.is_open()) {
    while (std::getline(filestream,line)) {;
      std::istringstream linestream(line);
      linestream >> key;
      std::vector<int> level_config;
      if (key == "Level") {
        while (linestream >> value) {
          level_config.push_back(std::stoi(value));
        }
        level_configs.push_back(level_config);
      }
    }
  }
  return level_configs;
}

void Game::getPoseFromSector(int sector,float &x,float &y) {
  int sector_size = (2*kScreenWidth + 2*kScreenHeight)/16;
  int p = sector*sector_size;
  if (p >=0 && p <= kScreenWidth) {
      y = 0.0;
      x = static_cast<float>( p % kScreenWidth );
  } else if (p > kScreenWidth && p <= (kScreenWidth + kScreenHeight)) {
      x = kScreenWidth;
      y = static_cast<float>( (p-kScreenWidth) % kScreenHeight );
  } else if (p > (kScreenWidth + kScreenHeight) && p <= (2*kScreenWidth + kScreenHeight)) {
      y = kScreenHeight;
      x = static_cast<float>( (p - kScreenWidth - kScreenHeight) % kScreenWidth );
  } else {
      y = static_cast<float>( (p - 2*kScreenWidth - kScreenHeight) % kScreenHeight );
      x = 0.0;
  }
}

void Game::setLevel(std::vector<int> level_config) {
  for (int sector = 0; sector < level_config.size(); sector++) {
    if (level_config[sector] == 1) {
      auto asteroid = std::make_unique<Asteroid>();
      float x, y;
      getPoseFromSector(sector,x,y);
      asteroid->setPose(x,y,asteroid->getPose().yaw);
      asteroids.push_back(std::move(asteroid));
    } else if (level_config[sector] == 2) {
      auto enemy = std::make_unique<Enemy>();
      float x, y;
      getPoseFromSector(sector,x,y);
      enemy->setPose(x,y,enemy->getPose().yaw);
      enemies.push_back(std::move(enemy));
    }
  }
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  level_configs = loadLevels();

  setLevel(level_configs[level]);

  while (running) {
    frame_start = SDL_GetTicks();
    if (asteroids.empty() && enemies.empty()) {
      level++;
      if (level < level_configs.size()) {
        setLevel(level_configs[level]);
      }
      else {
        running = false;
      }
    }

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, spaceship);
    Update();
    renderer.Render(spaceship, asteroids, enemies);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, level+1, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update() {
  if (!spaceship.isAlive()) {
    return;
  }

  // generate new asteroids
  std::vector<std::unique_ptr<Asteroid>> new_asteroids;
  for (std::unique_ptr<Asteroid> &asteroid : asteroids) {
    if (!asteroid->isAlive()) {
      for (int i = 0; i < asteroid->getNChildAsteroids(); i++) {
        new_asteroids.push_back(std::move(std::make_unique<Asteroid>(*asteroid.get())));
      }
    }
  }

  // remove dead asteroids
  if (!asteroids.empty()) {
    auto it = asteroids.begin();
    while (it != asteroids.end()) {
      std::unique_ptr<Asteroid> &asteroid = *it;
      if (asteroid->isAlive()) {
        ++it;
      } else {
        it = asteroids.erase(it);
      }
    }
  }

  // add new asteroids
  for (std::unique_ptr<Asteroid> &new_asteroid : new_asteroids) {
    asteroids.push_back(std::move(new_asteroid));
  }

  // remove dead enemies
  if (!enemies.empty()) {
    auto it = enemies.begin();
    while (it != enemies.end()) {
      std::unique_ptr<Enemy> &enemy = *it;
      if (enemy->isAlive()) {
        ++it;
      } else {
        it = enemies.erase(it);
      }
    }
  }

  // update player spaceship
  spaceship.Update();

  // update asteroids
  for (std::unique_ptr<Asteroid> &asteroid : asteroids) {
    asteroid->Update();
  }

  // update enemies
  for (std::unique_ptr<Enemy> &enemy : enemies) {
    enemy->Update(spaceship);
  }

  // check asteroid collisions
  for (std::unique_ptr<Asteroid> &asteroid : asteroids) {
    if (CollisionDetection::detect_collision(spaceship, *asteroid.get())) {
      spaceship.kill();
    }
    for (std::unique_ptr<Enemy> &enemy : enemies) {
      if (CollisionDetection::detect_collision(*enemy.get(), *asteroid.get())) {
        enemy->kill();
      }
    }
  }

  // check collisions with enemies
  for (std::unique_ptr<Enemy> &enemy : enemies) {
    if (CollisionDetection::detect_collision(spaceship, *enemy.get())) {
      if (enemy->render) {
        spaceship.kill();
      }
    }
  }

  // check enemy laser collisions
  // kill spaceship and laser if collision detected
  for (std::unique_ptr<Enemy> &enemy : enemies) {
    for (std::unique_ptr<Laser> &laser : enemy->lasers) {
      float x, y;
      laser->getFrontPoint(x,y);
      if (CollisionDetection::detect_point_collision(spaceship,x,y)) {
        laser->kill();
        spaceship.kill();
      }
    }
  }

  // check laser collisions
  // kill asteroid or enemy and laser if collision detected
  for (std::unique_ptr<Laser> &laser : spaceship.lasers) {
    float x, y;
    laser->getFrontPoint(x,y);

    // check asteroid collision
    for (std::unique_ptr<Asteroid> &asteroid : asteroids) {
      if (CollisionDetection::detect_point_collision(*asteroid.get(),x,y)) {
        laser->kill();
        asteroid->kill();
        score++;
      }
    }

    // check enemy collision
    for (std::unique_ptr<Enemy> &enemy : enemies) {
      if (CollisionDetection::detect_point_collision(*enemy.get(),x,y)) {
        laser->kill();
        enemy->kill();
        score++;
      }
    }
  }
}

int Game::GetScore() const { return score; }
