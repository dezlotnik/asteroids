#include "spaceship.h"
#include <math.h>
#include <iostream>

SpaceShip::SpaceShip() {

    spaceship_image_name_ = "../data/playerShip3_blue.png";
    spaceship_image_width_ = 37/1.5;
    spaceship_image_height_ = 49/1.5;

    respawn_image_name_ = "../data/playerShip3_blue_respawn.png";

    explosion_image_name_ = "../data/laserBlue10.png";
    explosion_image_width_ = 37/1.5;
    explosion_image_height_ = 37/1.5;

    setImageName(spaceship_image_name_);
    setWidth(spaceship_image_width_);
    setHeight(spaceship_image_height_);

    thruster.setImageName("../data/fire00.png");
    thruster.setWidth(40/1.5);
    thruster.setHeight(16/1.5);

    laser_image_name_ = "../data/laserBlue01.png";
    laser_range_ = 300;
    laser_speed_ = 10;
    reload_distance_ = 54;

    lives_ = 3;
    maximum_speed_ = 5.0;
}

void SpaceShip::Update() {

  manageStates();

  if (state_ == State::kAlive || state_ == State::kRespawn) {
    float speed = velocity_.velocity;
    float angular_velocity;
    float heading = velocity_.heading;

    float vx = speed*cos(heading*3.14/180.0);
    float vy = speed*sin(heading*3.14/180.0);
    float acceleration = 0.0;

    // set speed
    switch (thruster_state) {
        case ThrusterState::kAccelerate:
        acceleration = acceleration_;
        break;
        case ThrusterState::kNone:
        default :
        break;
    }

    // set angular velocity
    switch (rotate_state) {
        case RotateState::kLeft:
        angular_velocity = -10.0;
        break;
        case RotateState::kRight:
        angular_velocity = 10.0;
        break;
        case RotateState::kNone:
        default :
            angular_velocity = 0.0;
        break;
    }

    propagateState(acceleration, angular_velocity);

    // set thruster pose
    float x = -0.5*getWidth() - 0.5*thruster.getWidth();
    float y = 0; 
    float angle = pose_.yaw * 3.14/180.0;
    float xp = cos(angle)*x - sin(angle)*y;
    float yp = sin(angle)*x + cos(angle)*y;
    thruster.setPose(pose_.x + xp, pose_.y + yp, pose_.yaw);

    if (firing && state_ == State::kAlive) {
        Fire();
    }

    updateLasers();
  }

}