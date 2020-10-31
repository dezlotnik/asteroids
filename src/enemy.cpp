#include "enemy.h"
#include "spaceship.h"
#include <math.h>
#include <random>

Enemy::Enemy() : 
    engine(dev()),
    random_position(0,  2*kScreenWidth + 2*kScreenHeight)
{
    file_name = "../data/enemyRed2.png";
    image_width = 42;
    image_height = 52;

    laser_file_name = "../data/laserRed01.png";
    laser_range = 150;
    laser_speed = 5;

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

    std::uniform_real_distribution<float> random_speed(minimum_speed_, maximum_speed_);
    speed_ = random_speed(engine);

    setPose(x,y,0);
}

void Enemy::Update(const SpaceShip &spaceship) {
    if (!alive) {
      file_name = "../data/laserRed10.png";
      image_width = 37;
      image_height = 38;
      return;
    }

    float angle;
    float delta_x = spaceship.getPose().x - getPose().x;
    float delta_y = spaceship.getPose().y - getPose().y;
    
    angle = 180.0/3.14*atan2(delta_y,delta_x);

    setPose(getPose().x,getPose().y,angle);
    setVelocity(speed_, angle, 0.0);

    distance_to_player_ = sqrt(delta_x*delta_x + delta_y*delta_y);

    updatePose();
}