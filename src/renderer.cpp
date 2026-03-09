#include "renderer.h"
#include "car.h"
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "SDL_image.h"

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height)
    : screen_width(screen_width),
      screen_height(screen_height) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
  }

  sdl_window = SDL_CreateWindow("Carport Parking Simulator", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);

  // Create a 1x1 white texture for drawing colored rotated boxes.
  SDL_Surface* surface = SDL_CreateRGBSurface(0, 1, 1, 32, 0, 0, 0, 0);
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 255, 255));
  white_texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
  SDL_FreeSurface(surface);
}

Renderer::~Renderer() {
  SDL_DestroyTexture(white_texture);
  SDL_DestroyRenderer(sdl_renderer);
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

void Renderer::DrawCircle(int centerX, int centerY, int radius) {
  const int32_t diameter = (radius * 2);
  int32_t x = (radius - 1);
  int32_t y = 0;
  int32_t tx = 1;
  int32_t ty = 1;
  int32_t error = (tx - diameter);

  while (x >= y) {
    // Draw 8 octants
    SDL_RenderDrawPoint(sdl_renderer, centerX + x, centerY - y);
    SDL_RenderDrawPoint(sdl_renderer, centerX + x, centerY + y);
    SDL_RenderDrawPoint(sdl_renderer, centerX - x, centerY - y);
    SDL_RenderDrawPoint(sdl_renderer, centerX - x, centerY + y);
    SDL_RenderDrawPoint(sdl_renderer, centerX + y, centerY - x);
    SDL_RenderDrawPoint(sdl_renderer, centerX + y, centerY + x);
    SDL_RenderDrawPoint(sdl_renderer, centerX - y, centerY - x);
    SDL_RenderDrawPoint(sdl_renderer, centerX - y, centerY + x);

    if (error <= 0) {
      y++;
      error += ty;
      ty += 2;
    }
    if (error > 0) {
      x--;
      tx += 2;
      error += (tx - diameter);
    }
  }
}

void Renderer::RenderPolygon(const std::vector<GameObject::Point>& corners, SDL_Color color) {
  SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
  for (size_t i = 0; i < corners.size(); i++) {
    const auto& p1 = corners[i];
    const auto& p2 = corners[(i + 1) % corners.size()];
    SDL_RenderDrawLine(sdl_renderer, (int)p1.x, (int)p1.y, (int)p2.x, (int)p2.y);
  }
}

void Renderer::RenderTurningCircles(const Car &car) {
  if (std::abs(car.steering_angle) < 0.001) return;

  float r_center_ft = car.getRearAxleCenterRadiusFt();
  float r_left_ft = car.getRearLeftWheelRadiusFt();
  float r_right_ft = car.getRearRightWheelRadiusFt();

  float r_inner_ft = std::min(r_left_ft, r_right_ft);
  float r_outer_ft = std::max(r_left_ft, r_right_ft);

  if (std::abs(car.steering_angle) > 0.01) {
      std::cout << "Radii (ft) - Inner: " << r_inner_ft 
                << " | Center: " << r_center_ft 
                << " | Outer: " << r_outer_ft << "\r" << std::flush;
  }

  float yaw_rad = car.getPose().yaw * 3.14159 / 180.0;
  float wheelbase = car.getWheelbase();
  float lr = car.getLR();
  float width = car.getHeight(); // In yaw=0 orientation, height is width.

  // Rear axle center position
  float cx = car.getPose().x - lr * std::cos(yaw_rad);
  float cy = car.getPose().y - lr * std::sin(yaw_rad);

  // Instantaneous Center of Rotation (ICR)
  // Distance from center of rear axle to ICR
  float R_center = wheelbase / std::tan(car.steering_angle);
  
  // Right vector relative to car heading
  float rx = std::sin(yaw_rad);
  float ry = -std::cos(yaw_rad);

  // ICR position
  float icr_x = cx - R_center * rx;
  float icr_y = cy - R_center * ry;

  // Radii for rear wheels and center
  float r_axle = std::abs(R_center);
  float r_left = std::abs(R_center + width / 2.0f);
  float r_right = std::abs(R_center - width / 2.0f);

  // Draw circles
  SDL_SetRenderDrawBlendMode(sdl_renderer, SDL_BLENDMODE_BLEND);
  
  // Rear axle center - White
  SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 100);
  DrawCircle((int)icr_x, (int)icr_y, (int)r_axle);

  // Left wheel path - Yellow
  SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 0, 100);
  DrawCircle((int)icr_x, (int)icr_y, (int)r_left);

  // Right wheel path - Cyan
  SDL_SetRenderDrawColor(sdl_renderer, 0, 255, 255, 100);
  DrawCircle((int)icr_x, (int)icr_y, (int)r_right);
}

void Renderer::RenderGameObject(const GameObject *game_object) {
  SDL_Rect destination;
  destination.x = static_cast<int>(game_object->getPose().x - game_object->getWidth() / 2);
  destination.y = static_cast<int>(game_object->getPose().y - game_object->getHeight() / 2);
  destination.w = static_cast<int>(game_object->getWidth());
  destination.h = static_cast<int>(game_object->getHeight());

  if (game_object->use_color) {
    SDL_SetTextureColorMod(white_texture, game_object->color.r, game_object->color.g, game_object->color.b);
    SDL_SetTextureAlphaMod(white_texture, game_object->color.a);
    SDL_SetTextureBlendMode(white_texture, SDL_BLENDMODE_BLEND);
    SDL_RenderCopyEx(sdl_renderer, white_texture, NULL, &destination, game_object->getPose().yaw, NULL, SDL_FLIP_NONE);
  } else {
    SDL_Surface *surface = IMG_Load((game_object->getImageName()).c_str());
    if (surface) {
      SDL_Texture *texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
      SDL_FreeSurface(surface);
      SDL_RenderCopyEx(sdl_renderer, texture, NULL, &destination, game_object->getPose().yaw, NULL, SDL_FLIP_NONE);
      SDL_DestroyTexture(texture);
    }
  }
}

void Renderer::Render(const Car &car,
                      const std::vector<std::unique_ptr<GameObject>> &obstacles,
                      int m_x1, int m_y1, int m_x2, int m_y2,
                      int mouse_x, int mouse_y) {
  // Clear screen (Dark Gray)
  SDL_SetRenderDrawColor(sdl_renderer, 50, 50, 50, 255);
  SDL_RenderClear(sdl_renderer);

  // Render obstacles
  for (const auto &obstacle : obstacles) {
    RenderGameObject(obstacle.get());
  }

  // Render turning circles
  RenderTurningCircles(car);

  // Render car as Polygon
  SDL_Color car_color = {car.color.r, car.color.g, car.color.b, car.color.a};
  RenderPolygon(car.getCorners(), car_color);

  // Render forward indicator (Headlights strip)
  SDL_Rect head;
  float yaw_rad = car.getPose().yaw * 3.14159 / 180.0;
  // Front is at +length/2. Length is 162.
  float fx = car.getPose().x + (162.0f / 2.0f - 2.5f) * std::cos(yaw_rad);
  float fy = car.getPose().y + (162.0f / 2.0f - 2.5f) * std::sin(yaw_rad);
  
  head.x = (int)(fx - 2.5f);
  head.y = (int)(fy - 33.0f); // car half-width is 33
  head.w = 5;
  head.h = 66;

  SDL_SetTextureColorMod(white_texture, 255, 255, 255);
  SDL_SetTextureAlphaMod(white_texture, 255);
  SDL_RenderCopyEx(sdl_renderer, white_texture, NULL, &head, car.getPose().yaw, NULL, SDL_FLIP_NONE);

  // Render measuring line
  if (m_x1 != -1 && m_x2 != -1) {
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 0, 255); // Yellow
    SDL_RenderDrawLine(sdl_renderer, m_x1, m_y1, m_x2, m_y2);
  }

  // Render mouse crosshair
  if (mouse_x != -1 && mouse_y != -1) {
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 255); // White
    SDL_RenderDrawLine(sdl_renderer, mouse_x - 5, mouse_y, mouse_x + 5, mouse_y);
    SDL_RenderDrawLine(sdl_renderer, mouse_x, mouse_y - 5, mouse_x, mouse_y + 5);
  }

  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(float steering_angle, int fps, bool measure_mode, float measure_ft) {
  std::string title = "Parking Sim | Steering: " + std::to_string((int)steering_angle) + " deg | FPS: " + std::to_string(fps);
  if (measure_mode) {
    title += " | [MEASURE MODE]";
  }
  if (measure_ft > 0.001f) {
    title += " | Distance: " + std::to_string(measure_ft) + " ft";
  }
  SDL_SetWindowTitle(sdl_window, title.c_str());
}
