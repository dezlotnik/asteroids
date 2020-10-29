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
          spaceship.state = SpaceShip::State::kAccelerate;
          break;

        case SDLK_DOWN:
          spaceship.state = SpaceShip::State::kDecelerate;
          break;

        case SDLK_LEFT:
          spaceship.angle -= 20.0;
          break;

        case SDLK_RIGHT:
          spaceship.angle += 20.0;
          break;

        default :
          spaceship.state = SpaceShip::State::kDecelerate;
      }
    } else {
      spaceship.state = SpaceShip::State::kDecelerate;
    }
  }
}