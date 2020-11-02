#ifndef GAME_H
#define GAME_H

#include <random>
#include <vector>
#include <memory>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "spaceship.h"
#include "asteroid.h"
#include "laser.h"
#include "enemy.h"

class Game {
 public:
  Game(std::size_t screen_width, std::size_t screen_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  std::vector<std::vector<int>> loadLevels();
  void setLevel(std::vector<int> level_config);
  void getPoseFromSector(int sector,float &x,float &y);
  int level = 0;
  std::vector<std::vector<int>> level_configs;

 private:
  SpaceShip spaceship;
  std::vector<std::unique_ptr<Asteroid>> asteroids;
  std::vector<std::unique_ptr<Enemy>> enemies;

  int score{0};
  std::size_t screen_width;
  std::size_t screen_height;

  int n_asteroids = 1;
  int n_enemies = 2;

  void Update();
};

#endif