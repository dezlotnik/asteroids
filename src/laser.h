#ifndef LASER_H
#define LASER_H

#include <random>
#include "game_object.h"

class Ship;

class Laser : public GameObject {
public:
    Laser(const Ship &ship);
    void Update();
    float getDistance() {return distance_;}
    float getRange() {return range_;}
    void getFrontPoint(float &x, float &y);
private:
    float laser_speed_;
    float range_;
    float distance_ = 0.0;
};

#endif