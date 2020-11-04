#ifndef ENEMY_H
#define ENEMY_H

#include "ship.h"
#include "spaceship.h"
#include <vector>
#include <random>

class Enemy : public Ship {
public:
  Enemy();
  void Update(const SpaceShip &spaceship);
  float distanceToPlayer() { return distance_to_player_; }
  void controller(float yaw_error, float &acceleration,
                  float &angular_velocity);
  bool fire = true;
  bool render = true;

private:
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_position;
  float speed_range_max_ = 3.0;
  float speed_range_min_ = 2.0;
  float distance_to_player_ = 0.0;
};

#endif