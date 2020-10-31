#include "game.h"
#include <iostream>
#include <memory>
#include "SDL.h"
#include "collision_detection.h"

Game::Game(std::size_t screen_width, std::size_t screen_height) : 
      screen_width(screen_width),
      screen_height(screen_height) {
    spaceship.setPose(screen_width/2,screen_height/2,-90.0);

    for (size_t i = 0; i < n_asteroids; i++)
    {
        asteroids.push_back(std::make_shared<Asteroid>());
    }

    for (size_t i = 0; i < n_enemies; i++)
    {
        enemies.push_back(std::make_shared<Enemy>());
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

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, spaceship);
    Update();
    renderer.Render(spaceship, asteroids, lasers, enemies, enemy_lasers);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
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

  spaceship.Update();

  if (!spaceship.alive) {
    return;
  }

  // generate new asteroids
  std::vector<std::shared_ptr<Asteroid>> new_asteroids;
  for (std::shared_ptr<Asteroid> asteroid : asteroids) {
    if (!asteroid->alive) {
      for (int i = 0; i < asteroid->getNChildAsteroids(); i++) {
        new_asteroids.push_back(std::make_shared<Asteroid>(*asteroid.get()));
      }
    }
  }

  // remove dead asteroids
  if (!asteroids.empty()) {
    auto it = asteroids.begin();
    while (it != asteroids.end()) {
      std::shared_ptr<Asteroid> &asteroid = *it;
      if (asteroid->alive) {
        ++it;
      } else {
        it = asteroids.erase(it);
      }
    }
  }

  // add new asteroids
  for (std::shared_ptr<Asteroid> new_asteroid : new_asteroids) {
    asteroids.push_back(new_asteroid);
  }

  // respawn asteroids
  if (asteroids.size() < n_asteroids) {
    for (int i = 0; i < (n_asteroids - asteroids.size()); i++) {
      asteroids.push_back(std::make_shared<Asteroid>());
    }
  }

  // remove dead enemies
  if (!enemies.empty()) {
    auto it = enemies.begin();
    while (it != enemies.end()) {
      std::shared_ptr<Enemy> &enemy = *it;
      if (enemy->alive) {
        ++it;
      } else {
        it = enemies.erase(it);
      }
    }
  }

  // respawn enemies
  if (enemies.size() < n_enemies) {
    for (int i = 0; i < (n_enemies - enemies.size()); i++) {
      enemies.push_back(std::make_shared<Enemy>());
    }
  }

  // update asteroids
  for (std::shared_ptr<Asteroid> asteroid : asteroids) {
    asteroid->Update();
  }

  // update enemies
  for (std::shared_ptr<Enemy> enemy : enemies) {
    enemy->Update(spaceship);
    if (enemy_lasers.empty() && (enemy->distanceToPlayer() < enemy->laser_range)) {
      enemy_lasers.push_back(std::make_shared<Laser>(*enemy.get()));
    }
  }

  // update lasers
  if (spaceship.firing) {
    if (lasers.empty()) {
      lasers.push_back(std::make_shared<Laser>(spaceship));
    } else if (lasers.back()->getDistance() > lasers.back()->image_width) {
      lasers.push_back(std::make_shared<Laser>(spaceship));
    }
  }

  // remove dead lasers
  if (!lasers.empty()) {
    auto it = lasers.begin();
    while (it != lasers.end()) {
      std::shared_ptr<Laser> &laser = *it;
      laser->Update();
      if (laser->getDistance() < laser->getRange() && laser->alive) {
          ++it;
      } else {
          it = lasers.erase(it);
      }
    }
  }

  // remove dead enemy lasers
  if (!enemy_lasers.empty()) {
    auto it = enemy_lasers.begin();
    while (it != enemy_lasers.end()) {
      std::shared_ptr<Laser> &laser = *it;
      laser->Update();
      if (laser->getDistance() < laser->getRange() && laser->alive) {
          ++it;
      } else {
          it = enemy_lasers.erase(it);
      }
    }
  }

  // check asteroid collisions
  for (std::shared_ptr<Asteroid> asteroid : asteroids) {
    if (CollisionDetection::detect_collision(spaceship, *asteroid.get())) {
      spaceship.alive = false;
    }
    for (std::shared_ptr<Enemy> enemy : enemies) {
      if (CollisionDetection::detect_collision(*enemy.get(), *asteroid.get())) {
        enemy->hit = true;
      }
    }
  }

  // check collisions with enemies
  for (std::shared_ptr<Enemy> enemy : enemies) {
    if (CollisionDetection::detect_collision(spaceship, *enemy.get())) {
      spaceship.alive = false;
    }
  }

  // check enemy laser collisions
  // kill spaceship and laser if collision detected
  for (std::shared_ptr<Laser> laser : enemy_lasers) {
    float x, y;
    laser->getFrontPoint(x,y);
    if (CollisionDetection::detect_point_collision(spaceship,x,y)) {
      laser->alive = false;
      spaceship.alive = false;
    }
  }

  // check laser collisions
  // kill asteroid or enemy and laser if collision detected
  for (std::shared_ptr<Laser> laser : lasers) {
    float x, y;
    laser->getFrontPoint(x,y);

    // check asteroid collision
    for (std::shared_ptr<Asteroid> asteroid : asteroids) {
      if (CollisionDetection::detect_point_collision(*asteroid.get(),x,y)) {
        laser->alive = false;
        asteroid->alive = false;
        score++;
      }
    }

    // check enemy collision
    for (std::shared_ptr<Enemy> enemy : enemies) {
      if (CollisionDetection::detect_point_collision(*enemy.get(),x,y)) {
        laser->alive = false;
        enemy->hit = true;
        score++;
      }
    }
  }
}

int Game::GetScore() const { return score; }
