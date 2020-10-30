#include "laser.h"
#include "spaceship.h"

Laser::Laser(const GameObject &game_object) {
    file_name = "../data/laserBlue01.png";
    image_height = 54;
    image_width = 9;

    // set laser pose
    float x = 0;
    float y = -0.5*game_object.image_height;
    float angle = game_object.getPose().angle * 3.14/180.0;
    float xp = cos(angle)*x - sin(angle)*y;
    float yp = sin(angle)*x + cos(angle)*y;
    setPose(game_object.getPose().x + xp, game_object.getPose().y + yp, game_object.getPose().angle);

    // set laser velocity
    setVelocity(laser_speed_, game_object.getPose().angle, 0);
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