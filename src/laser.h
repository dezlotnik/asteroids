#ifndef LASER_H
#define LASER_H

#include <random>
#include "game_object.h"
#include "spaceship.h"

class Laser : public GameObject {
public:
    Laser(const SpaceShip &spaceship);
    void Update();
    float getDistance() {return distance_;}
    float getRange() {return range_;}
private:
    float laser_speed_ = 10;
    float range_ = 250;
    float distance_ = 0.0;
};

#endif