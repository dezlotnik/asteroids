#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "car.h"

void Controller::HandleInput(bool &running, Car &car) const {
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
    }
  }
}
