#ifndef SHIP_H
#define SHIP_H

#include "game_object.h"
#include <chrono>
#include <memory>

class Laser;

class Ship : public GameObject {
public:
  std::vector<std::unique_ptr<Laser>> lasers;
  void Fire();
  void updateLasers();
  std::string getLaserImageName() const { return laser_image_name_; }
  float getLaserRange() const { return laser_range_; }
  float getLaserSpeed() const { return laser_speed_; }
  int getLives() { return lives_; }
  void propagateState(float acceleration, float angular_velocity);
  enum class State { kAlive, kExploding, kRespawn };
  void explode();
  void respawn();
  void manageStates();
  void kill() override;

protected:
  std::string laser_image_name_;
  float laser_range_;
  float laser_speed_;
  float reload_distance_;
  std::chrono::time_point<std::chrono::system_clock> kill_time_;
  std::chrono::time_point<std::chrono::system_clock> respawn_time_;
  long explosion_duration_ = 300; // milliseconds
  long respawn_duration_ = 2000;  // milliseconds
  State state_ = State::kAlive;
  int lives_;

  std::string spaceship_image_name_;
  float spaceship_image_width_;
  float spaceship_image_height_;

  std::string respawn_image_name_;

  std::string explosion_image_name_;
  float explosion_image_width_;
  float explosion_image_height_;
};

#endif