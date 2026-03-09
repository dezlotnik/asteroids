#include "car.h"
#include <cmath>
#include <iostream>
#include <algorithm>

Car::Car() {
  setWidth(162);   // BMW X5 Length (~16.2 ft)
  setHeight(66);   // BMW X5 Width (~6.6 ft)
  use_color = true;
  color = {0, 122, 204, 255}; // Blue

  // Define vertices for BMW X5 with Side Mirrors (relative to center)
  // Length: 162px, Width: 66px
  // Mirrors: at x = +30 (front-third), 9 inches wide (9px)
  
  float half_l = 81.0f;
  float half_w = 33.0f;
  float mirror_ext = 4.2f; // 4.2 inches extension per side
  float mirror_x = 30.0f;  // Positioning mirrors towards the front
  float mirror_w = 5.0f;   // Thickness of mirror

  // 12-point polygon: 
  // Nose (2), Front-Right Mirror (3), Rear-Right (1), Rear-Left (1), Front-Left Mirror (3), Nose-Left (2)
  vertices_ = {
    {half_l, -half_w + 5},      // Front Right bumper corner (slightly tapered)
    {mirror_x + mirror_w, -half_w}, // Right mirror start
    {mirror_x + mirror_w, -half_w - mirror_ext}, // Right mirror tip front
    {mirror_x - mirror_w, -half_w - mirror_ext}, // Right mirror tip back
    {mirror_x - mirror_w, -half_w}, // Right mirror end
    {-half_l + 5, -half_w},     // Rear Right corner
    {-half_l + 5, half_w},      // Rear Left corner
    {mirror_x - mirror_w, half_w},  // Left mirror start back
    {mirror_x - mirror_w, half_w + mirror_ext},  // Left mirror tip back
    {mirror_x + mirror_w, half_w + mirror_ext},  // Left mirror tip front
    {mirror_x + mirror_w, half_w},  // Left mirror end front
    {half_l, half_w - 5}        // Front Left bumper corner (slightly tapered)
  };

  lives_ = 3;
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

  float dyaw_rad = (speed / L) * tan(steering_angle);

  float dx = speed * cos(yaw_rad) - (dyaw_rad * lr * sin(yaw_rad));
  float dy = speed * sin(yaw_rad) + (dyaw_rad * lr * cos(yaw_rad));

  pose_.x += dx;
  pose_.y += dy;
  pose_.yaw += dyaw_rad * 180.0 / 3.14159;
}
