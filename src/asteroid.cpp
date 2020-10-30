#include "asteroid_constants.h"
#include "asteroid.h"
#include <iostream>
#include <tuple>

using namespace AsteroidConstants;

std::tuple<std::string, int, int> METIOR_1 = {"../data/meteorBrown_big1.png", 101, 85};
std::tuple<std::string, int, int> METIOR_2 = {"../data/meteorBrown_med1.png", 43, 43};
std::tuple<std::string, int, int> METIOR_3 = {"../data/meteorBrown_small1.png", 28, 28};

Asteroid::Asteroid() :
    engine(dev()),
    random_heading(0.0, 360.0),
    random_speed(1.0, 5.0),
    random_angular_velocity(0.5,5.0),
    random_position(0,  2*kScreenWidth + 2*kScreenHeight)
{
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

    setVelocity(random_speed(engine),random_heading(engine),random_angular_velocity(engine));
    setPose(x,y,0);

    file_name = std::get<0>(METIOR_1);
    image_width = std::get<1>(METIOR_1);
    image_height = std::get<2>(METIOR_1);

    n_child_asteroids_ = 0;
}

Asteroid::Asteroid(const Asteroid &asteroid_parent) :
    engine(dev()),
    random_heading(0.0, 360.0),
    random_speed(1.0, 5.0),
    random_angular_velocity(0.5,5.0)
{
    pose_ = asteroid_parent.pose_;
    setVelocity(random_speed(engine),random_heading(engine),random_angular_velocity(engine));

    if (asteroid_parent.file_name ==  std::get<0>(METIOR_1)) {
        file_name = std::get<0>(METIOR_2);
        image_width = std::get<1>(METIOR_2);
        image_height = std::get<2>(METIOR_2);
        n_child_asteroids_ = 0;
    } else if (asteroid_parent.file_name ==  std::get<0>(METIOR_2)) {
        file_name = std::get<0>(METIOR_3);
        image_width = std::get<1>(METIOR_3);
        image_height = std::get<2>(METIOR_3);
        n_child_asteroids_ = 0;
    }
}