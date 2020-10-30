#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "spaceship.h"
#include "asteroid.h"
#include "laser.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(SpaceShip const &spaceship, std::vector<std::shared_ptr<Asteroid>> asteroids, std::vector<std::shared_ptr<Laser>> lasers);
  void RenderGameObject(const GameObject *game_object);
  void UpdateWindowTitle(int score, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif