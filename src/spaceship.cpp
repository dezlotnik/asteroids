#include "spaceship.h"
#include <math.h>

SpaceShip::SpaceShip() {
    file_name = "../data/playerShip3_blue.png";
    image_width = 49;
    image_height = 37;

    thruster.file_name = "../data/fire00.png";
    thruster.image_width = 16;
    thruster.image_height = 40;

    laser_file_name = "../data/laserBlue01.png";
    laser_range = 500;
    laser_speed = 10;
}

void SpaceShip::Update() {

  if (!alive) {
      file_name = "../data/laserBlue10.png";
      image_width = 37;
      image_height = 37;
      return;
  }

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

  // set thruster pose
  float x = 0;
  float y = 0.5*image_height + 0.5*thruster.image_height;
  float angle = pose_.angle * 3.14/180.0;
  float xp = cos(angle)*x - sin(angle)*y;
  float yp = sin(angle)*x + cos(angle)*y;
  thruster.setPose(pose_.x + xp, pose_.y + yp, pose_.angle);

}