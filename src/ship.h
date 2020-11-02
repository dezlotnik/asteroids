#ifndef SHIP_H
#define SHIP_H

#include "game_object.h"

class Laser;

class Ship : public GameObject {
public:
    std::vector<std::unique_ptr<Laser>> lasers;
    void Fire();
    void updateLasers();
    std::string getLaserImageName() const {return laser_image_name_;}
    float getLaserRange() const {return laser_range_;}
    float getLaserSpeed() const {return laser_speed_;}
    void propagateState(float acceleration, float angular_velocity);
protected:
    std::string laser_image_name_;
    float laser_range_;
    float laser_speed_;
    float reload_distance_;
};

#endif