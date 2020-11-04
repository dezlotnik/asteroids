#include <math.h>
#include "game_object.h"
#include "asteroid_constants.h"

using namespace AsteroidConstants;

void GameObject::setPose(float x, float y, float yaw) {
  pose_.x = x;
  pose_.y = y;
  pose_.yaw = yaw;
}

void GameObject::setVelocity(float velocity, float heading, float angular_velocity) {
  if (velocity > getMaximumSpeed()) {
    velocity_.velocity = getMaximumSpeed();
  } else if (velocity < getMinimumSpeed()) {
    velocity_.velocity = getMinimumSpeed();
  } else {
    velocity_.velocity = velocity;
  }
  velocity_.heading = heading;
  velocity_.angular_velocity = angular_velocity;
}

void GameObject::updatePose() {
  float new_x, new_y, new_yaw;
  new_x = getPose().x +
          cos((velocity_.heading) * 3.14 / 180.0) * velocity_.velocity;
  new_y = getPose().y +
          sin((velocity_.heading) * 3.14 / 180.0) * velocity_.velocity;
  new_yaw = getPose().yaw + velocity_.angular_velocity;

  new_x = fmod(new_x + kScreenWidth, kScreenWidth);
  new_y = fmod(new_y + kScreenHeight, kScreenHeight);
  setPose(new_x, new_y, new_yaw);
}