#include "spaceship.h"

SpaceShip::SpaceShip() {
    file_name = "../data/playerShip3_blue.png";
    image_width = 49;
    image_height = 37;
}

void SpaceShip::Update() {
  float speed = velocity_.velocity;
  float angular_velocity;
  float heading;

  // set speed
  switch (thruster_state) {
    case ThrusterState::kAccelerate:
      speed += 1;
      break;
    case ThrusterState::kDecelerate:
      speed -= 0.2;
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
      angular_velocity = 0.0;
    default :
      break;
  }

  heading = pose_.angle;

  setVelocity(speed, heading, angular_velocity);
  updatePose();
}