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

 private:
  SpaceShip spaceship;
  std::vector<std::shared_ptr<Asteroid>> asteroids;
  std::vector<std::shared_ptr<Laser>> lasers;
  std::vector<std::shared_ptr<Enemy>> enemies;
  std::vector<std::shared_ptr<Laser>> enemy_lasers;

  int score{0};
  std::size_t screen_width;
  std::size_t screen_height;

  void Update();
};

#endif