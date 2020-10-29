#include "renderer.h"
#include "spaceship.h"
#include <iostream>
#include <string>
#include "SDL_image.h"

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

void Renderer::Render(SpaceShip const &spaceship) {
  SDL_Rect block;
  block.w = screen_width / grid_width;
  block.h = screen_height / grid_height;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer);

  // Render spaceship
//   block.x = static_cast<int>(spaceship.position_x) * block.w;
//   block.y = static_cast<int>(spaceship.position_y) * block.h;
  
//   SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
//   // allocate space for 3 points
//   SDL_Point *points = new SDL_Point[3];
//   float h = spaceship.side_length/2.0*0.577;
//   points[0].x = static_cast<int>( spaceship.position_x - spaceship.side_length/2.0 );
//   points[0].y = static_cast<int>( spaceship.position_y - h);
//   points[1].x = static_cast<int>( spaceship.position_x );
//   points[1].y = static_cast<int>( spaceship.position_y - 1.5*spaceship.side_length);
//   points[2].x = points[0].x + spaceship.side_length;
//   points[2].y = points[0].y;

//   SDL_RenderDrawLines(sdl_renderer,points,3);
//   delete[] points;

  SDL_Surface* surface = IMG_Load("playerShip3_blue.png"); 
  // printf("IMG_Load: %s\n", IMG_GetError());
  SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface); 
  SDL_FreeSurface(surface);
  SDL_Rect destination;
  destination.x = static_cast<int>( spaceship.position_x - 49/2);
  destination.y = static_cast<int>( spaceship.position_y - 37/2);
  destination.w = 49;
  destination.h = 37;

  SDL_RendererFlip flip = SDL_FLIP_NONE;
  SDL_RenderCopyEx(sdl_renderer, texture, NULL, &destination, spaceship.angle, NULL, flip );
 

  // Render spaceship
//   block.x = static_cast<int>(spaceship.position_x) * block.w;
//   block.y = static_cast<int>(spaceship.position_y) * block.h;
//   if (spaceship.alive) {
//     SDL_SetRenderDrawColor(sdl_renderer, 0x00, 0x7A, 0xCC, 0xFF);
//   } else {
//     SDL_SetRenderDrawColor(sdl_renderer, 0xFF, 0x00, 0x00, 0xFF);
//   }
//   SDL_RenderFillRect(sdl_renderer, &block);

  // Update Screen
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps) {
  std::string title{"Asteroids Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window, title.c_str());
}