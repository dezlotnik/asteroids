#include "laser.h"
#include "spaceship.h"

Laser::Laser(const Ship &ship) {
    file_name = ship.laser_file_name;
    image_height = 54;
    image_width = 9;
    laser_speed_ = ship.laser_speed;
    range_ = ship.laser_range;

    // set laser pose
    float x = 0;
    float y = -0.5*ship.image_height;
    float angle = ship.getPose().angle * 3.14/180.0;
    float xp = cos(angle)*x - sin(angle)*y;
    float yp = sin(angle)*x + cos(angle)*y;
    setPose(ship.getPose().x + xp, ship.getPose().y + yp, ship.getPose().angle);

    // set laser velocity
    setVelocity(laser_speed_, ship.getPose().angle, 0);
}

void Laser::Update() {
     updatePose();
     distance_ += laser_speed_;
}

void Laser::getFrontPoint(float &x, float &y) {
    float x_f = 0;
    float y_f = -image_height/2.0;
    float angle = pose_.angle * 3.14/180.0;
    x = pose_.x + cos(angle)*x_f - sin(angle)*y_f;
    y = pose_.y + sin(angle)*x_f + cos(angle)*y_f;
}