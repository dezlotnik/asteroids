#ifndef ASTEROID_H
#define ASTEROID_H

#include <random>
#include "game_object.h"

class Asteroid : public GameObject {
public:
    Asteroid();
    void Update() {updatePose();}
private:
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<float> random_x;
  std::uniform_int_distribution<float> random_y;
  std::uniform_int_distribution<float> random_speed;
  std::uniform_int_distribution<float> random_heading;
};

#endif