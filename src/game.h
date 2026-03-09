#ifndef GAME_H
#define GAME_H

#include <vector>
#include <memory>
#include <string>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "car.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  void Reset();

  // Measuring tool
  struct Point { int x, y; };
  Point measure_p1 = {-1, -1};
  Point measure_p2 = {-1, -1};
  Point mouse_pos = {-1, -1};
  bool measure_mode = false;
  bool is_measuring = false;
  float current_measure_ft = 0.0f;

  struct GeometryConfig {
    float driveway_width = 25.95f;
    float driveway_depth = 9.61f;
    float carport_door_width = 10.0f;
    float carport_inside_width = 11.25f;
    float carport_inside_depth = 25.25f;
    float alley_width = 12.5f;
    float carport_x_offset = 0.0f; // Offset from screen center (400)
    float driveway_x_offset = -1.0f; // Offset from carport left post
    float car_start_x = 70.0f; // ft along alley
    float car_start_y_offset = 3.0f; // ft from alley centerline
    float car_start_facing_right = 0.0f; // 1 for right, 0 for left
  };

 private:
  Car car;
  std::vector<std::unique_ptr<GameObject>> obstacles;

  std::size_t screen_width;
  std::size_t screen_height;

  GeometryConfig config;
  void LoadGeometryConfig(std::string path);
  void BuildEnvironment();
  void Update();
};

#endif
