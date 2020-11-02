#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "ship.h"
#include "laser.h"
#include <vector>
#include <string>

class SpaceShip : public Ship {
public:
    SpaceShip();
    void Update();
    enum class ThrusterState { kNone, kAccelerate};
    enum class RotateState { kNone, kLeft, kRight };
    ThrusterState thruster_state = ThrusterState::kNone;
    RotateState rotate_state = RotateState::kNone;
    GameObject thruster;
    bool firing{false};

private:
    float acceleration_ = 0.5;
};

#endif