#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "ship.h"
#include "laser.h"
#include <vector>
#include <string>

class SpaceShip : public Ship {
public:

    static const float kSpaceShipWidth;
    static const float kSpaceShipHeight;
    static const std::string kSpaceShipImageName;

    static const float kExplosionWidth;
    static const float kExplosionHeight;
    static const std::string kExplosionImageName;

    static const std::string kLaserImageName;

    static const float kThrusterWidth;
    static const float kThrusterHeight;
    static const std::string kThrusterImageName;

    static const float kLaserRange;
    static const float kLaserSpeed;
    static const float kLaserReloadDistance;

    SpaceShip();
    void Update();
    float getMaximumSpeed() override {return maximum_speed_;}
    void kill() override;
    enum class ThrusterState { kNone, kAccelerate};
    enum class RotateState { kNone, kLeft, kRight };
    ThrusterState thruster_state = ThrusterState::kNone;
    RotateState rotate_state = RotateState::kNone;
    GameObject thruster;
    bool firing{false};

private:
    float maximum_speed_ = 5.0;
    float acceleration_ = 0.5;
};

#endif