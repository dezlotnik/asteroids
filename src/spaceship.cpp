#include <math.h>
#include "spaceship.h"

void SpaceShip::Update() {
  float new_speed = speed;

  switch (thruster_state) {
    case ThrusterState::kAccelerate:
      new_speed += 1;
      if (new_speed > 10.0) {
        new_speed = 10.0;
      }
      break;
    case ThrusterState::kDecelerate:
      new_speed -= 0.2;
      if (new_speed < 0.0) {
        new_speed = 0.0;
      }
      break;
    case ThrusterState::kNone:
    default :
      break;
  }

  switch (rotate_state) {
    case RotateState::kLeft:
      angle -= 10.0;
      break;
    case RotateState::kRight:
      angle += 10.0;
      break;
    case RotateState::kNone:
    default :
      break;
  }

  speed = new_speed;
  position_x -= cos((angle + 90.0) * 3.14/180.0) * speed;
  position_y -= sin((angle + 90.0) * 3.14/180.0) * speed;
  position_x = fmod(position_x + screen_width, screen_width);
  position_y = fmod(position_y + screen_height, screen_height);
}