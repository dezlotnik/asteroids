#include "game.h"
#include <iostream>
#include "SDL.h"
#include <math.h>

Game::Game(std::size_t screen_width, std::size_t screen_height) : 
      screen_width(screen_width),
      screen_height(screen_height) {
    spaceship.position_x = 320;
    spaceship.position_y = 320;
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
    renderer.Render(spaceship);

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
  float new_speed = spaceship.speed;

  switch (spaceship.thruster_state) {
    case SpaceShip::ThrusterState::kAccelerate:
      new_speed += 1;
      if (new_speed > 10.0) {
        new_speed = 10.0;
      }
      break;
    case SpaceShip::ThrusterState::kDecelerate:
      new_speed -= 0.2;
      if (new_speed < 0.0) {
        new_speed = 0.0;
      }
      break;
  }

  switch (spaceship.rotate_state) {
    case SpaceShip::RotateState::kLeft:
      spaceship.angle -= 10.0;
      break;
    case SpaceShip::RotateState::kRight:
      spaceship.angle += 10.0;
      break;
  }

  spaceship.speed = new_speed;
  spaceship.position_x -= cos((spaceship.angle + 90.0) * 3.14/180.0) * spaceship.speed;
  spaceship.position_y -= sin((spaceship.angle + 90.0) * 3.14/180.0) * spaceship.speed;
  spaceship.position_x = fmod(spaceship.position_x + screen_width, screen_width);
  spaceship.position_y = fmod(spaceship.position_y + screen_height, screen_height);
}

int Game::GetScore() const { return 0; }
int Game::GetSize() const { return 0; }