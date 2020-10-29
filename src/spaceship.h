#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "game_object.h"

class SpaceShip : public GameObject {
public:
    SpaceShip();
    void Update();
    enum class ThrusterState { kNone, kAccelerate, kDecelerate };
    enum class RotateState { kNone, kLeft, kRight };
    bool alive{true};
    ThrusterState thruster_state = ThrusterState::kNone;
    RotateState rotate_state = RotateState::kNone;

private:
};

#endif