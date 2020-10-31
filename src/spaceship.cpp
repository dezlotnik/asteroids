#include "spaceship.h"
#include <math.h>
#include <iostream>

SpaceShip::SpaceShip() {
    file_name = "../data/playerShip3_blue.png";
    image_height = 49;
    image_width = 37;

    thruster.file_name = "../data/fire00.png";
    thruster.image_height = 16;
    thruster.image_width = 40;

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
  float heading = velocity_.heading;

  float vx = speed*cos(heading*3.14/180.0);
  float vy = speed*sin(heading*3.14/180.0);

  // set speed
  switch (thruster_state) {
    case ThrusterState::kAccelerate:
      //speed += 1;
      vx += 0.1*cos(pose_.angle*3.14/180.0);
      vy += 0.1*sin(pose_.angle*3.14/180.0);
      speed = sqrt(vx*vx + vy*vy);
      //heading -= 0.1*(heading - pose_.angle);
      heading = -180.0/3.14*atan2(vx,vy) + 90.0;
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

  //heading = pose_.angle;
//   vx = speed*cos(heading);
//   vy = speed*sin(heading);
//   heading = 180.0/3.14*atan2(vx,-vy) + 90.0;
  std::cout << "heading = " << heading << "\n";
  std::cout << "angle = " << pose_.angle << "\n";

  

  setVelocity(speed, heading, angular_velocity);
  updatePose();

  // set thruster pose
  float x = -0.5*image_width - 0.5*thruster.image_width;
  float y = 0; 
  float angle = pose_.angle * 3.14/180.0;
  float xp = cos(angle)*x - sin(angle)*y;
  float yp = sin(angle)*x + cos(angle)*y;
  thruster.setPose(pose_.x + xp, pose_.y + yp, pose_.angle);

}