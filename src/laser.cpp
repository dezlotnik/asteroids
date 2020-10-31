#include "laser.h"
#include "spaceship.h"

Laser::Laser(const Ship &ship) {

    setImageName(ship.laser_image_name);
    setWidth(54);
    setHeight(9);

    laser_speed_ = ship.laser_speed;
    range_ = ship.laser_range;

    // set laser pose
    float x = 0.5*ship.getHeight();
    float y = 0;
    float angle = ship.getPose().yaw * 3.14/180.0;
    float xp = cos(angle)*x - sin(angle)*y;
    float yp = sin(angle)*x + cos(angle)*y;
    setPose(ship.getPose().x + xp, ship.getPose().y + yp, ship.getPose().yaw);

    // set laser velocity
    setVelocity(laser_speed_, ship.getPose().yaw, 0);
}

void Laser::Update() {
     updatePose();
     distance_ += laser_speed_;
}

void Laser::getFrontPoint(float &x, float &y) {
    float x_f = getHeight()/2.0;
    float y_f = 0;
    float angle = pose_.yaw * 3.14/180.0;
    x = pose_.x + cos(angle)*x_f - sin(angle)*y_f;
    y = pose_.y + sin(angle)*x_f + cos(angle)*y_f;
}