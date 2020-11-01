#include "renderer.h"
#include "spaceship.h"
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "asteroid.h"
#include "laser.h"
#include "enemy.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width),
      screen_height(screen_height) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window = SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::RenderGameObject(const GameObject *game_object) {
    SDL_Surface* surface = IMG_Load((game_object->getImageName()).c_str()); 
    // printf("IMG_Load: %s\n", IMG_GetError());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface); 
    SDL_FreeSurface(surface);
    SDL_Rect destination;
    destination.x = static_cast<int>(game_object->getPose().x - game_object->getWidth()/2);
    destination.y = static_cast<int>(game_object->getPose().y - game_object->getHeight()/2);
    destination.w = game_object->getWidth();
    destination.h = game_object->getHeight();
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(sdl_renderer, texture, NULL, &destination, game_object->getPose().yaw, NULL, flip );
    SDL_DestroyTexture(texture);

    // SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    // SDL_RenderDrawRect(sdl_renderer,&destination);
}

void Renderer::Render(const SpaceShip &spaceship,
                      const std::vector<std::unique_ptr<Asteroid>> &asteroids,
                      const std::vector<std::unique_ptr<Enemy>> &enemies) {

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render asteroids
  for (const std::unique_ptr<Asteroid> &asteroid : asteroids) {
    RenderGameObject(asteroid.get());
  }

  // Render thruster
  if (spaceship.thruster_state == SpaceShip::ThrusterState::kAccelerate && spaceship.isAlive()) {
    RenderGameObject(&(spaceship.thruster));
  }

  // render lasers
  for (const std::unique_ptr<Laser> &laser: spaceship.lasers) {
    RenderGameObject(laser.get());
  }

  // Render spaceship
  RenderGameObject(&spaceship);
  

  // Render enemies
  for (const std::unique_ptr<Enemy> &enemy : enemies) {
    for (const std::unique_ptr<Laser> &laser: enemy->lasers) {
      RenderGameObject(laser.get());
    }
    if (enemy->render) {
      RenderGameObject(enemy.get());
    }
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int level, int fps) {
  std::string title{"Asteroids! Score: " + std::to_string(score) + " Level: " + std::to_string(level) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}