#ifndef ENEMY_H
#define ENEMY_H

#include "ship.h"
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
    static const float kLaserRange;
    static const float kLaserSpeed;

    Enemy();
    void Update(const SpaceShip &spaceship);
    void kill() override;
    float getMaximumSpeed() override {return maximum_speed_;}
    float distanceToPlayer() {return distance_to_player_;}
    void controller(float yaw_error, float &acceleration, float &angular_velocity);
    bool fire = true;
    bool render = true;

private:
    std::random_device dev;
    std::mt19937 engine;
    std::uniform_int_distribution<int> random_position;

    float maximum_speed_ = 5.0;
    float minimum_speed_ = 0.0;
    float speed_;
    float distance_to_player_ = 0.0;
    int counter_ = 0;
    std::chrono::time_point<std::chrono::system_clock> kill_time_;
    long explosion_duration_ = 100; //milliseconds
    bool exploding_ = false;

};

#endif