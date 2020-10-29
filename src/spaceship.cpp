#include <math.h>
#include "spaceship.h"

void SpaceShip::Update() {
  float speed = velocity_.velocity;
  float angular_velocity;

  // set speed
  switch (thruster_state) {
    case ThrusterState::kAccelerate:
      speed += 1;
      if (speed > 10.0) {
        speed = 10.0;
      }
      break;
    case ThrusterState::kDecelerate:
      speed -= 0.2;
      if (speed < 0.0) {
        speed = 0.0;
      }
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

  setVelocity(speed, angular_velocity);
  updatePose();
}