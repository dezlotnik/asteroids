#ifndef SPACESHIP_H
#define SPACESHIP_H


class SpaceShip {
public:
    SpaceShip() {}
    enum class ThrusterState { kNone, kAccelerate, kDecelerate };
    enum class RotateState { kNone, kLeft, kRight };
    bool alive{true};
    float position_x;
    float position_y;
    float angle = 0.0;
    float side_length = 20; // length in pixels
    float speed = 0.0;
    ThrusterState thruster_state = ThrusterState::kNone;
    RotateState rotate_state = RotateState::kNone;

private:

};
#endif