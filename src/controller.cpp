#include "controller.h"
#include <iostream>
#include <SDL2/SDL.h>

void Controller::HandleInput(bool &running) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    }
  }
}