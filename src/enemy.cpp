#include "enemy.h"
#include "spaceship.h"
#include <math.h>

Enemy::Enemy() {
    file_name = "../data/enemyRed2.png";
    image_width = 52;
    image_height = 42;

    laser_file_name = "../data/laserRed01.png";
    laser_range = 250;
    laser_speed = 10;

    setPose(100,100,0);
}

void Enemy::Update(const SpaceShip &spaceship) {
    float angle;
    float delta_x = getPose().x - spaceship.getPose().x;
    float delta_y = getPose().y - spaceship.getPose().y;
    
    angle = -180.0/3.14*atan2(delta_x, delta_y);

    setPose(getPose().x,getPose().y,angle);
    setVelocity(getMaximumSpeed(), angle, 0.0);

    distance_to_player_ = sqrt(delta_x*delta_x + delta_y*delta_y);

    updatePose();
}