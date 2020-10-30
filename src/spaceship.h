#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "game_object.h"
#include <vector>

class SpaceShip : public GameObject {
public:
    SpaceShip();
    void Update();
    enum class ThrusterState { kNone, kAccelerate, kDecelerate };
    enum class RotateState { kNone, kLeft, kRight };
    ThrusterState thruster_state = ThrusterState::kNone;
    RotateState rotate_state = RotateState::kNone;
    GameObject thruster;
    bool fire{false};

private:
};

#endif