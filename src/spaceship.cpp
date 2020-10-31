#include "spaceship.h"
#include <math.h>
#include <iostream>

const std::string SpaceShip::kSpaceShipImageName = "../data/playerShip3_blue.png";
const float SpaceShip::kSpaceShipHeight = 49/1.5;
const float SpaceShip::kSpaceShipWidth = 37/1.5;

const std::string SpaceShip::kExplosionImageName = "../data/laserBlue10.png";
const float SpaceShip::kExplosionWidth = 37/1.5;
const float SpaceShip::kExplosionHeight = 37/1.5;

const std::string SpaceShip::kLaserImageName = "../data/laserBlue01.png";

const std::string SpaceShip::kThrusterImageName = "../data/fire00.png";
const float SpaceShip::kThrusterWidth = 40/1.5;
const float SpaceShip::kThrusterHeight = 16/1.5;

SpaceShip::SpaceShip() {

    setImageName(kSpaceShipImageName);
    setWidth(kSpaceShipWidth);
    setHeight(kSpaceShipHeight);

    thruster.setImageName(kThrusterImageName);
    thruster.setWidth(kThrusterWidth);
    thruster.setHeight(kThrusterHeight);

    laser_image_name = kLaserImageName;
    laser_range = 500;
    laser_speed = 10;
}

void SpaceShip::kill() {
    alive_ = false;
    setImageName(kExplosionImageName);
    setWidth(kExplosionWidth);
    setHeight(kExplosionHeight);
}

void SpaceShip::Update() {

  if (!isAlive()) {
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
      vx += acceleration_*cos(pose_.yaw*3.14/180.0);
      vy += acceleration_*sin(pose_.yaw*3.14/180.0);
      speed = sqrt(vx*vx + vy*vy);
      heading = 180.0/3.14*atan2(vy,vx);
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

  setVelocity(speed, heading, angular_velocity);
  updatePose();

  // set thruster pose
  float x = -0.5*getWidth() - 0.5*thruster.getWidth();
  float y = 0; 
  float angle = pose_.yaw * 3.14/180.0;
  float xp = cos(angle)*x - sin(angle)*y;
  float yp = sin(angle)*x + cos(angle)*y;
  thruster.setPose(pose_.x + xp, pose_.y + yp, pose_.yaw);

}