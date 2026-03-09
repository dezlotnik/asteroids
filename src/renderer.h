#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include "SDL.h"
#include "car.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height);
  ~Renderer();

  void Render(const Car &car,
              const std::vector<std::unique_ptr<GameObject>> &obstacles);
  void RenderGameObject(const GameObject *game_object);
  void RenderTurningCircles(const Car &car);
  void DrawCircle(int x, int y, int radius);
  void UpdateWindowTitle(float steering_angle, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *white_texture;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif
