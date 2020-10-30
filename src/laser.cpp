#include "laser.h"
#include "spaceship.h"

Laser::Laser(const SpaceShip &spaceship) {
    file_name = "../data/laserBlue01.png";
    image_height = 54;
    image_width = 9;

    // set laser pose
    float x = 0;
    float y = -0.5*spaceship.image_height - 0.5*image_height;
    float angle = spaceship.getPose().angle * 3.14/180.0;
    float xp = cos(angle)*x - sin(angle)*y;
    float yp = sin(angle)*x + cos(angle)*y;
    setPose(spaceship.getPose().x + xp, spaceship.getPose().y + yp, spaceship.getPose().angle);

    // set laser velocity
    setVelocity(laser_speed_, spaceship.getPose().angle, 0);
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