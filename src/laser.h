#ifndef LASER_H
#define LASER_H

#include <random>
#include "game_object.h"
#include "spaceship.h"

class Laser : public GameObject {
public:
    Laser(const SpaceShip &spaceship);
    void Update() {updatePose();}
private:
    float laser_speed_ = 10;
};

#endif