#ifndef SHIP_H
#define SHIP_H

#include "game_object.h"

class Laser;

class Ship : public GameObject {
public:
    std::string laser_image_name;
    float laser_range;
    float laser_speed;
    float reload_distance;
    std::vector<std::unique_ptr<Laser>> lasers;
    void Fire();
    void updateLasers();
};

#endif