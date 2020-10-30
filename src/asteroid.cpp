#include "asteroid.h"
#include <iostream>
#include <tuple>

std::tuple<std::string, int, int> METIOR_1 = {"../data/meteorBrown_big1.png", 101, 85};
std::tuple<std::string, int, int> METIOR_2 = {"../data/meteorBrown_med1.png", 43, 43};
std::tuple<std::string, int, int> METIOR_3 = {"../data/meteorBrown_small1.png", 28, 28};

Asteroid::Asteroid() :
    engine(dev()),
    random_heading(0.0, 360.0),
    random_speed(1.0, 5.0),
    random_angular_velocity(0.5,5.0),
    random_position(0, 2560) //640 * 4
{
    int p = random_position(engine);
    float y;
    float x;

    if (p >=0 && p <= 640) {
        y = 0.0;
        x = static_cast<float>( p % 640 );
    } else if (p > 640 && p <= 640*2) {
        x = 640.0;
        y = static_cast<float>( p % 640 );
    } else if (p > 640*2 && p <= 640*3) {
        y = 640.0;
        x = static_cast<float>( p % 640 );
    } else {
        y = static_cast<float>( p % 640 );
        x = 0.0;
    }

    setVelocity(random_speed(engine),random_heading(engine),random_angular_velocity(engine));
    setPose(x,y,0);

    file_name = std::get<0>(METIOR_1);
    image_width = std::get<1>(METIOR_1);
    image_height = std::get<2>(METIOR_1);

    n_child_asteroids_ = 2;
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
        n_child_asteroids_ = 2;
    } else if (asteroid_parent.file_name ==  std::get<0>(METIOR_2)) {
        file_name = std::get<0>(METIOR_3);
        image_width = std::get<1>(METIOR_3);
        image_height = std::get<2>(METIOR_3);
        n_child_asteroids_ = 0;
    }
}