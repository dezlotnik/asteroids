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
              const std::vector<std::unique_ptr<GameObject>> &obstacles,
              int m_x1 = -1, int m_y1 = -1, int m_x2 = -1, int m_y2 = -1,
              int mouse_x = -1, int mouse_y = -1);
  void RenderGameObject(const GameObject *game_object);
  void RenderTurningCircles(const Car &car);
  void DrawCircle(int x, int y, int radius);
  void UpdateWindowTitle(float steering_angle, int fps, bool measure_mode, float measure_ft = 0.0f);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Texture *white_texture;

  const std::size_t screen_width;
  const std::size_t screen_height;
};

#endif
