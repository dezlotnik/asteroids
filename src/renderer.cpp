#include "renderer.h"
#include "spaceship.h"
#include <iostream>
#include <string>
#include "SDL_image.h"
#include "asteroid.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height) {
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
    SDL_Surface* surface = IMG_Load((game_object->file_name).c_str()); 
    // printf("IMG_Load: %s\n", IMG_GetError());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface); 
    SDL_FreeSurface(surface);
    SDL_Rect destination;
    destination.x = static_cast<int>(game_object->getPose().x - game_object->image_width/2);
    destination.y = static_cast<int>(game_object->getPose().y - game_object->image_height/2);
    destination.w = game_object->image_width;
    destination.h = game_object->image_height;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(sdl_renderer, texture, NULL, &destination, game_object->getPose().angle, NULL, flip );

    // SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    // SDL_RenderDrawRect(sdl_renderer,&destination);
}

void Renderer::Render(SpaceShip const &spaceship, std::vector<std::shared_ptr<Asteroid>> asteroids) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render spaceship
  RenderGameObject(&spaceship);

  // Render thruster
  if (spaceship.thruster_state == SpaceShip::ThrusterState::kAccelerate) {
    SDL_Surface* surface = IMG_Load("../data/fire00.png"); 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface); 
    SDL_FreeSurface(surface);
    SDL_Rect destination;
    float x = -16/2;
    float y = 1.0/2.0*spaceship.image_height;
    float angle = spaceship.getPose().angle * 3.14/180.0;
    float xp = cos(angle)*x - sin(angle)*y;
    float yp = sin(angle)*x + cos(angle)*y;
    destination.x = static_cast<int>(spaceship.getPose().x + xp);
    destination.y = static_cast<int>(spaceship.getPose().y + yp);
    // destination.x = static_cast<int>(spaceship.getPose().x);
    // destination.y = static_cast<int>(spaceship.getPose().y);
    destination.w = 16;
    destination.h = 40;
    SDL_Point p;
    p.x = 0;
    p.y = 0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    SDL_RenderCopyEx(sdl_renderer, texture, NULL, &destination, (spaceship.getPose().angle), &p, flip);

    // SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
    // SDL_RenderDrawRect(sdl_renderer,&destination);
  }
 
  // Render asteroids
  for (std::shared_ptr<Asteroid> asteroid : asteroids) {
    RenderGameObject(asteroid.get());
  }

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Asteroids Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}