#include "enemy.h"
#include "spaceship.h"
#include <math.h>
#include <random>

const float Enemy::kEnemyWidth = 42/1.5;
const float Enemy::kEnemyHeight = 52/1.5;
const std::string Enemy::kEnemyImageName = "../data/enemyRed2.png";

const float Enemy::kExplosionWidth = 37/1.5;
const float Enemy::kExplosionHeight = 38/1.5;
const std::string Enemy::kExplosionImageName = "../data/laserRed10.png";

const std::string Enemy::kLaserImageName = "../data/laserRed01.png";

Enemy::Enemy() : 
    engine(dev()),
    random_position(0,  2*kScreenWidth + 2*kScreenHeight)
{
    setImageName(kEnemyImageName);
    setWidth(kEnemyWidth);
    setHeight(kEnemyHeight);

    laser_image_name = kLaserImageName;
    laser_range = 500;
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
    if (hit) {
      setImageName(kExplosionImageName);
      setWidth(kExplosionWidth);
      setHeight(kExplosionHeight);

      if (counter_ > 5) {
          alive = false;
      }
      counter_++;
      return;
    }

    float yaw;
    float delta_x = spaceship.getPose().x - getPose().x;
    float delta_y = spaceship.getPose().y - getPose().y;
    
    yaw = 180.0/3.14*atan2(delta_y,delta_x);

    setPose(getPose().x,getPose().y,yaw);
    setVelocity(speed_, yaw, 0.0);

    distance_to_player_ = sqrt(delta_x*delta_x + delta_y*delta_y);

    updatePose();
}