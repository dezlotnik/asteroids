#include <math.h>
#include "spaceship.h"

void SpaceShip::Update() {
  float new_speed = speed;

  switch (thruster_state) {
    case SpaceShip::ThrusterState::kAccelerate:
      new_speed += 1;
      if (new_speed > 10.0) {
        new_speed = 10.0;
      }
      break;
    case SpaceShip::ThrusterState::kDecelerate:
      new_speed -= 0.2;
      if (new_speed < 0.0) {
        new_speed = 0.0;
      }
      break;
  }

  switch (rotate_state) {
    case SpaceShip::RotateState::kLeft:
      angle -= 10.0;
      break;
    case SpaceShip::RotateState::kRight:
      angle += 10.0;
      break;
  }

  speed = new_speed;
  position_x -= cos((angle + 90.0) * 3.14/180.0) * speed;
  position_y -= sin((angle + 90.0) * 3.14/180.0) * speed;
  position_x = fmod(position_x + screen_width, screen_width);
  position_y = fmod(position_y + screen_height, screen_height);
}