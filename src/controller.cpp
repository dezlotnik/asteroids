#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "car.h"
#include "game.h"

void Controller::HandleInput(bool &running, Car &car, Game &game) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          car.throttle_state = Car::ThrottleState::kForward;
          break;
        case SDLK_DOWN:
          car.throttle_state = Car::ThrottleState::kReverse;
          break;
        case SDLK_LEFT:
          car.steering_state = Car::SteeringState::kLeft;
          break;
        case SDLK_RIGHT:
          car.steering_state = Car::SteeringState::kRight;
          break;
        case SDLK_r:
          game.Reset();
          break;
        case SDLK_t:
          car.setPose(car.getPose().x, car.getPose().y, car.getPose().yaw + 180.0f);
          break;
        case SDLK_m:
          game.measure_mode = !game.measure_mode;
          if (!game.measure_mode) {
            game.measure_p1 = {-1, -1};
            game.measure_p2 = {-1, -1};
            game.current_measure_ft = 0.0f;
            game.is_measuring = false;
          }
          break;
        default :
          break;
      }
    } else if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          if (car.throttle_state == Car::ThrottleState::kForward)
            car.throttle_state = Car::ThrottleState::kNone;
          break;
        case SDLK_DOWN:
          if (car.throttle_state == Car::ThrottleState::kReverse)
            car.throttle_state = Car::ThrottleState::kNone;
          break;
        case SDLK_LEFT:
          if (car.steering_state == Car::SteeringState::kLeft)
            car.steering_state = Car::SteeringState::kNone;
          break;
        case SDLK_RIGHT:
          if (car.steering_state == Car::SteeringState::kRight)
            car.steering_state = Car::SteeringState::kNone;
          break;
        default:
          break;
      }
    } else if (e.type == SDL_MOUSEBUTTONDOWN) {
      if (game.measure_mode && e.button.button == SDL_BUTTON_LEFT) {
        game.measure_p1 = {e.button.x, e.button.y};
        game.measure_p2 = {e.button.x, e.button.y};
        game.mouse_pos = {e.button.x, e.button.y};
        game.is_measuring = true;
      }
    } else if (e.type == SDL_MOUSEMOTION) {
      game.mouse_pos = {e.motion.x, e.motion.y};
      if (game.measure_mode && game.is_measuring) {
        game.measure_p2 = {e.motion.x, e.motion.y};
      }
    } else if (e.type == SDL_MOUSEBUTTONUP) {
      if (game.measure_mode && e.button.button == SDL_BUTTON_LEFT) {
        game.measure_p2 = {e.button.x, e.button.y};
        game.mouse_pos = {e.button.x, e.button.y};
        game.is_measuring = false;
      }
    }
  }
}
