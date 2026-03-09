#include "car.h"
#include <math.h>
#include <iostream>
#include <algorithm>

Car::Car() {
  setWidth(162);   // BMW X5 Length (~16.2 ft)
  setHeight(66);   // BMW X5 Width (~6.6 ft)
  use_color = true;
  color = {0, 122, 204, 255}; // Blue

  lives_ = 3;
  // 2.0 px/frame * 60 fps = 120 px/s = 12 ft/s = ~8 mph (Responsive parking speed)
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
      // Instantaneous Braking
      speed = 0.0;
    }
    speed = std::min(maximum_speed_, std::max(minimum_speed_, speed));

    // Steering (Persists at last value)
    if (steering_state == SteeringState::kLeft) {
      steering_angle = std::max(-max_steering_angle, steering_angle - steering_speed);
    } else if (steering_state == SteeringState::kRight) {
      steering_angle = std::min(max_steering_angle, steering_angle + steering_speed);
    }

    updatePose();
  }
}

void Car::updatePose() {
  // yaw is in degrees. Convert to radians for math.
  float yaw_rad = pose_.yaw * 3.14159 / 180.0;
  
  // wheelbase L = 98px
  // Distance from Rear Axle to Geometric Center lr = 46px
  float lr = 46.0;
  float L = 98.0;

  // 1. Calculate rotation rate
  // dPsi = (V / L) * tan(delta)
  float dyaw_rad = (speed / L) * tan(steering_angle);

  // 2. Calculate velocity of the geometric center
  // The rear axle moves exactly in the direction of yaw.
  // The center also has a component from the rotation.
  float dx = speed * cos(yaw_rad) - (dyaw_rad * lr * sin(yaw_rad));
  float dy = speed * sin(yaw_rad) + (dyaw_rad * lr * cos(yaw_rad));

  // 3. Apply movement
  pose_.x += dx;
  pose_.y += dy;
  pose_.yaw += dyaw_rad * 180.0 / 3.14159;
}
