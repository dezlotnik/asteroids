#include <math.h>
#include "game_object.h"
#include "parking_constants.h"

using namespace ParkingConstants;

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
          cos((velocity_.heading) * 3.14159 / 180.0) * velocity_.velocity;
  new_y = getPose().y +
          sin((velocity_.heading) * 3.14159 / 180.0) * velocity_.velocity;
  new_yaw = getPose().yaw + velocity_.angular_velocity;

  setPose(new_x, new_y, new_yaw);
}

std::vector<GameObject::Point> GameObject::getCorners() const {
  std::vector<Point> corners;
  float rad = pose_.yaw * 3.14159 / 180.0;
  float c = cos(rad);
  float s = sin(rad);

  if (!vertices_.empty()) {
    for (const auto& v : vertices_) {
      corners.push_back({
          pose_.x + v.x * c - v.y * s,
          pose_.y + v.x * s + v.y * c
      });
    }
    return corners;
  }

  float half_w = width_ / 2.0;
  float half_h = height_ / 2.0;

  float dx[4] = {-half_w, half_w, half_w, -half_w};
  float dy[4] = {-half_h, -half_h, half_h, half_h};

  for (int i = 0; i < 4; i++) {
    corners.push_back({
        pose_.x + dx[i] * c - dy[i] * s,
        pose_.y + dx[i] * s + dy[i] * c
    });
  }
  return corners;
}
