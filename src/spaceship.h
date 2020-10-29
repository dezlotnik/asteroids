#ifndef SPACESHIP_H
#define SPACESHIP_H


class SpaceShip {
public:
    SpaceShip() {}
    enum class State { kNone, kAccelerate, kDecelerate };
    bool alive{true};
    float position_x;
    float position_y;
    float angle = 0.0;
    float side_length = 20; // length in pixels
    float speed = 0.0;
    State state = State::kNone;

private:

};
#endif