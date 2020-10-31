#ifndef ENEMY_H
#define ENEMY_H

#include "game_object.h"
#include "spaceship.h"
#include <vector>
#include <random>

class Enemy : public Ship {
public:

    static const float kEnemyWidth;
    static const float kEnemyHeight;
    static const std::string kEnemyImageName;

    static const float kExplosionWidth;
    static const float kExplosionHeight;
    static const std::string kExplosionImageName;

    static const std::string kLaserImageName;

    Enemy();
    void Update(const SpaceShip &spaceship);
    float getMaximumSpeed() override {return maximum_speed_;}
    float distanceToPlayer() {return distance_to_player_;}
    bool fire = true;
    bool hit = false;

private:
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_position;

    float maximum_speed_ = 2.0;
    float minimum_speed_ = 1.0;
    float speed_;
    float distance_to_player_ = 0.0;
    int counter_ = 0;
};

#endif