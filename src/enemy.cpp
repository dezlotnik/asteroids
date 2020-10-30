#include "enemy.h"
#include "spaceship.h"
#include <math.h>

Enemy::Enemy() {
    file_name = "../data/enemyRed2.png";
    image_width = 52;
    image_height = 42;

    setPose(100,100,0);
}

void Enemy::Update(const SpaceShip &spaceship) {
    float angle;
    
    angle = -180.0/3.14*atan2(getPose().x - spaceship.getPose().x, getPose().y - spaceship.getPose().y);

    setPose(getPose().x,getPose().y,angle);
    setVelocity(getMaximumSpeed(), angle, 0.0);

    updatePose();
}