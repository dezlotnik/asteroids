
#include "ship.h"
#include "laser.h"

void Ship::Fire() {
  if (lasers.empty()) {
    lasers.push_back(std::make_unique<Laser>((*this)));
  } else if (lasers.back()->getDistance() > reload_distance_) {
    lasers.push_back(std::make_unique<Laser>(*this));
  }
}

void Ship::updateLasers() {
  if (!lasers.empty()) {
    auto it = lasers.begin();
    while (it != lasers.end()) {
      std::unique_ptr<Laser> &laser = *it;
      laser->Update();
      if (laser->getDistance() < laser->getRange() && laser->isAlive()) {
          ++it;
      } else {
          it = lasers.erase(it);
      }
    }
  }
}

void Ship::propagateState(float acceleration, float angular_velocity) {
  float speed = velocity_.velocity;
  float heading = velocity_.heading;
  float vx = speed*cos(heading*3.14/180.0);
  float vy = speed*sin(heading*3.14/180.0);
  vx += acceleration*cos(pose_.yaw*3.14/180.0);
  vy += acceleration*sin(pose_.yaw*3.14/180.0);
  speed = sqrt(vx*vx + vy*vy);
  heading = 180.0/3.14*atan2(vy,vx);
  
  setVelocity(speed,heading,angular_velocity);
  updatePose();
}

void Ship::kill() {
  if (state_ == State::kAlive) {
    kill_time_ = std::chrono::system_clock::now();
    state_ = State::kExploding;
    setImageName(explosion_image_name_);
    setWidth(explosion_image_width_);
    setHeight(explosion_image_height_);
    lives_--;
  }
}

void Ship::explode() {
  long time_since_explosion = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - kill_time_).count();
  if (time_since_explosion >=  explosion_duration_) {
    if (lives_ > 0) {
      respawn_time_ =  std::chrono::system_clock::now();
      setPose(kScreenWidth/2,kScreenHeight/2,-90.0);
      setVelocity(0,0,0);
      setImageName(respawn_image_name_);
      setWidth(spaceship_image_width_);
      setHeight(spaceship_image_height_);
      state_ = State::kRespawn;
    } else {
      alive_ = false;
    }
  }
}

void Ship::respawn() {
  long time_since_respawn = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - respawn_time_).count();
  if (time_since_respawn >=  respawn_duration_) {
    setImageName(spaceship_image_name_);
    setWidth(spaceship_image_width_);
    setHeight(spaceship_image_height_);
    state_ = State::kAlive;
    alive_ = true;
  }
}

void Ship::manageStates() {
  switch (state_) {
    case State::kAlive :
      break;
    case State::kExploding :
      explode();
      break;
    case State::kRespawn :
      respawn();
      break;
    default :
      break;
  }
}