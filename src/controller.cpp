#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "spaceship.h"

void Controller::HandleInput(bool &running, SpaceShip &spaceship) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          spaceship.thruster_state = SpaceShip::ThrusterState::kAccelerate;
          break;

        case SDLK_DOWN:
          //spaceship.state = SpaceShip::State::kDecelerate;
          break;

        case SDLK_LEFT:
          spaceship.rotate_state = SpaceShip::RotateState::kLeft;
          break;

        case SDLK_RIGHT:
          spaceship.rotate_state = SpaceShip::RotateState::kRight;
          break;

        case SDLK_SPACE:
          spaceship.firing = true;
          break;

        default :
          break;
          //spaceship.state = SpaceShip::State::kDecelerate;
      }
    } else if (e.type == SDL_KEYUP) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          spaceship.thruster_state = SpaceShip::ThrusterState::kDecelerate;
          break;

        case SDLK_DOWN:
          //spaceship.state = SpaceShip::State::kDecelerate;
          break;

        case SDLK_LEFT:
          spaceship.rotate_state = SpaceShip::RotateState::kNone;
          break;

        case SDLK_RIGHT:
          spaceship.rotate_state = SpaceShip::RotateState::kNone;
          break;

        case SDLK_SPACE:
          spaceship.firing = false;
          break;

        default :
          break;
    }
  }
}
}