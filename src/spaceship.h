#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "game_object.h"
#include <vector>

class SpaceShip : public Ship {
public:
    SpaceShip();
    void Update();
    float getMaximumSpeed() override {return maximum_speed_;}
    enum class ThrusterState { kNone, kAccelerate, kDecelerate };
    enum class RotateState { kNone, kLeft, kRight };
    ThrusterState thruster_state = ThrusterState::kNone;
    RotateState rotate_state = RotateState::kNone;
    GameObject thruster;
    bool firing{false};

private:
    float maximum_speed_ = 5.0;
};

#endif