#ifndef CAR_H
#define CAR_H

#include "game_object.h"
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

class Car : public GameObject {
public:
  Car();
  void Update();
  void updatePose() override;
  enum class ThrottleState { kNone, kForward, kReverse };
  enum class SteeringState { kNone, kLeft, kRight, kFlip };
  ThrottleState throttle_state = ThrottleState::kNone;
  SteeringState steering_state = SteeringState::kNone;
  
  float steering_angle = 0.0;
  float speed = 0.0;
  bool is_flipped = false;
  
  // Adjusted for Outside Front Wheel Turning Radius of 20.65ft
  const float max_steering_angle = 33.4 * 3.14159 / 180.0;
  const float wheelbase = 98.0;
  const float lr = 46.0; 
  const float steering_speed = 0.01; // Reduced from 0.04 for more precision
  const float auto_center_speed = 0.02;
  const float acceleration = 0.1;
  const float friction = 0.05;

  enum class State { kAlive, kExploding, kRespawn };
  State state_ = State::kAlive;

  int getLives() const { return lives_; }
  float getWheelbase() const { return wheelbase; }
  float getLR() const { return lr; }
  float getSteeringAngleDeg() const { return steering_angle * 180.0 / 3.14159; }

  // Radii in feet (Scale: 10px = 1ft)
  float getRearAxleCenterRadiusFt() const {
    if (std::abs(steering_angle) < 0.001) return 0.0f;
    return std::abs((wheelbase / std::tan(steering_angle)) / 10.0f);
  }
  float getRearLeftWheelRadiusFt() const {
    if (std::abs(steering_angle) < 0.001) return 0.0f;
    float R_center = wheelbase / std::tan(steering_angle);
    return std::abs((R_center + height_ / 2.0f) / 10.0f);
  }
  float getRearRightWheelRadiusFt() const {
    if (std::abs(steering_angle) < 0.001) return 0.0f;
    float R_center = wheelbase / std::tan(steering_angle);
    return std::abs((R_center - height_ / 2.0f) / 10.0f);
  }

private:
  int lives_ = 3;
};

#endif
