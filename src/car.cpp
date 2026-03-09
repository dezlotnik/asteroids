#include "car.h"
#include <cmath>
#include <iostream>
#include <algorithm>

Car::Car() {
  setWidth(162);   // BMW X5 Length (~16.2 ft)
  setHeight(66);   // BMW X5 Width (~6.6 ft)
  use_color = true;
  color = {0, 122, 204, 255}; // Blue

  lives_ = 3;
  // 2.0 px/frame * 60 fps = 120 px/s = 12 ft/s = ~8 mph
  maximum_speed_ = 2.0;
  minimum_speed_ = -2.0;
}

void Car::Update() {
  if (state_ == State::kAlive) {
    // Throttle / Braking
    if (throttle_state == ThrottleState::kForward) {
      speed += acceleration;
    } else if (throttle_state == ThrottleState::kReverse) {
      speed -= acceleration;
    } else {
      speed = 0.0;
    }
    speed = std::min(maximum_speed_, std::max(minimum_speed_, speed));

    // Steering
    if (steering_state == SteeringState::kLeft) {
      steering_angle = std::max(-max_steering_angle, steering_angle - steering_speed);
    } else if (steering_state == SteeringState::kRight) {
      steering_angle = std::min(max_steering_angle, steering_angle + steering_speed);
    }

    updatePose();
  }
}

void Car::updatePose() {
  float yaw_rad = pose_.yaw * 3.14159 / 180.0;
  float L = 98.0; // Wheelbase
  float lr = 46.0; // Dist from center to rear axle

  // 1. Angular velocity
  float dyaw_rad = (speed / L) * tan(steering_angle);

  // 2. Linear velocity of geometric center
  // Derived from: V_center = V_rear + omega x r_center/rear
  // V_rear is always [v*cos(psi), v*sin(psi)]
  float dx = speed * cos(yaw_rad) - (dyaw_rad * lr * sin(yaw_rad));
  float dy = speed * sin(yaw_rad) + (dyaw_rad * lr * cos(yaw_rad));

  pose_.x += dx;
  pose_.y += dy;
  pose_.yaw += dyaw_rad * 180.0 / 3.14159;
}
