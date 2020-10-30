#include "game.h"
#include <iostream>
#include <memory>
#include "SDL.h"
#include "collision_detection.h"

Game::Game(std::size_t screen_width, std::size_t screen_height) : 
      screen_width(screen_width),
      screen_height(screen_height) {
    spaceship.setPose(screen_width/2,screen_height/2,0.0);
    int nAsteroids = 5;
    for (size_t i = 0; i < nAsteroids; i++)
    {
        asteroids.push_back(std::make_shared<Asteroid>());
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
    renderer.Render(spaceship, asteroids, lasers);

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
  // if (!spaceship.alive) {
  //   return;
  // }

  if (asteroids.empty()) {
    for (int i = 0; i < 5; i++) {
      asteroids.push_back(std::make_shared<Asteroid>());
    }
  }

  spaceship.Update();

  for (std::shared_ptr<Asteroid> asteroid : asteroids) {
    asteroid->Update();
  }

  if (spaceship.fire) {
    lasers.push_back(std::make_shared<Laser>(spaceship));
    spaceship.fire = false;
  }

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

  // check asteroid collisions
  for (std::shared_ptr<Asteroid> asteroid : asteroids) {
    if (CollisionDetection::detect_collision(spaceship, *asteroid.get())) {
      spaceship.alive = false;
      // std::cout << "Collision Detected!!!" << "\n";
    } else {
      // std::cout << "No collision." << "\n";
    }
  }

  // check laser collisions
  // remove asteroid if collision detected
  for (std::shared_ptr<Laser> laser : lasers) {
    auto it = asteroids.begin();
    while (it != asteroids.end()) {
      std::shared_ptr<Asteroid> &asteroid = *it;
      float x, y;
      laser->getFrontPoint(x,y);
      if (CollisionDetection::detect_point_collision(*asteroid.get(),x,y)) {
        it = asteroids.erase(it);
        laser->alive = false;
        //std::cout << "Collision Detected!!!" << "\n";
      } else {
        ++it;
        //std::cout << "No collision." << "\n";
      }
    }
  }
}

int Game::GetScore() const { return 0; }
