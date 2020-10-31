#ifndef ENEMY_H
#define ENEMY_H

#include "game_object.h"
#include "spaceship.h"
#include <vector>

class Enemy : public Ship {
public:
    Enemy();
    void Update(const SpaceShip &spaceship);
    float getMaximumSpeed() override {return maximum_speed_;}
    float distanceToPlayer() {return distance_to_player_;}
    bool fire = true;

private:
    float maximum_speed_ = 3.0;
    float distance_to_player_ = 0.0;
};

#endif