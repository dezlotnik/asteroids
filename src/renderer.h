#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "spaceship.h"
#include "asteroid.h"
#include "laser.h"
#include "enemy.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(const SpaceShip &spaceship,
              const std::vector<std::unique_ptr<Asteroid>> &asteroids,
              const std::vector<std::unique_ptr<Enemy>> &enemies);
  void RenderGameObject(const GameObject *game_object);
  void UpdateWindowTitle(int score, int level, int lives, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif