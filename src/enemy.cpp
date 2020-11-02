#include "enemy.h"
#include "spaceship.h"
#include <math.h>
#include <random>
#include <iostream>

Enemy::Enemy() : 
    engine(dev()),
    random_position(0,  2*kScreenWidth + 2*kScreenHeight)
{
    spaceship_image_name_ = "../data/enemyRed2.png";
    spaceship_image_width_ = 42/1.5;
    spaceship_image_height_ = 52/1.5;

    explosion_image_name_ = "../data/laserRed10.png";
    explosion_image_width_ = 37/1.5;
    explosion_image_height_ = 38/1.5;

    setImageName(spaceship_image_name_);
    setWidth(spaceship_image_width_);
    setHeight(spaceship_image_height_);

    laser_image_name_ = "../data/laserRed01.png";
    laser_range_ = 300;
    laser_speed_ = 5;
    reload_distance_ = laser_range_;

    int p = random_position(engine);
    float y;
    float x;

    if (p >=0 && p <= kScreenWidth) {
        y = 0.0;
        x = static_cast<float>( p % kScreenWidth );
    } else if (p > kScreenWidth && p <= (kScreenWidth + kScreenHeight)) {
        x = kScreenWidth;
        y = static_cast<float>( (p-kScreenWidth) % kScreenHeight );
    } else if (p > (kScreenWidth + kScreenHeight) && p <= (2*kScreenWidth + kScreenHeight)) {
        y = kScreenHeight;
        x = static_cast<float>( (p - kScreenWidth - kScreenHeight) % kScreenWidth );
    } else {
        y = static_cast<float>( (p - 2*kScreenWidth - kScreenHeight) % kScreenHeight );
        x = 0.0;
    }

    std::uniform_real_distribution<float> random_speed(speed_range_min_, speed_range_max_);
    maximum_speed_ = random_speed(engine);

    setPose(x,y,0);

    lives_ = 1;
}


void Enemy::controller(float yaw_error, float &acceleration, float &angular_velocity) {
    angular_velocity = yaw_error;
    acceleration = 0.25;
}

void Enemy::Update(const SpaceShip &spaceship) {
    manageStates();

    if (state_ == State::kAlive) {
        float yaw;
        float delta_x = spaceship.getPose().x - getPose().x;
        float delta_y = spaceship.getPose().y - getPose().y;

        distance_to_player_ = sqrt(delta_x*delta_x + delta_y*delta_y);
        
        yaw = 180.0/3.14*atan2(delta_y,delta_x);

        float angular_velocity, acceleration;
        float yaw_error = yaw - getPose().yaw;
        controller(yaw_error, acceleration, angular_velocity);

        propagateState(acceleration,angular_velocity);

        if (distanceToPlayer() <= laser_range_) {
            Fire();
        }
    }
    updateLasers();
}