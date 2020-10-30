#ifndef ASTEROID_H
#define ASTEROID_H

#include <random>
#include "game_object.h"

class Asteroid : public GameObject {
public:
    Asteroid();
    Asteroid(const Asteroid &asteroid_parent);
    void Update() {updatePose();}
    int getNChildAsteroids() {return n_child_asteroids_;}
private:
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_real_distribution<float> random_speed;
  std::uniform_real_distribution<float> random_heading;
  std::uniform_real_distribution<float> random_angular_velocity;
  std::uniform_int_distribution<int> random_position;

  int n_child_asteroids_;
};

#endif