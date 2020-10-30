#include "asteroid.h"
#include <iostream>

Asteroid::Asteroid() :
    engine(dev()),
    random_heading(0, static_cast<float>(360)),
    random_speed(2, static_cast<float>(5)),
    random_angular_velocity(0.5,5.0),
    random_position(0, static_cast<int>(2560)) //640 * 4
{
    int p = random_position(engine);
    float y;
    float x;

    if (p >=0 && p <= 640) {
        y = 0.0;
        x = static_cast<float>( p % 640 );
    } else if (p > 640 && p <=640*2) {
        x = 640.0;
        y = static_cast<float>( p % 640 );
    } else if (p > 640*2 && p <=640*3) {
        y = 640.0;
        x = static_cast<float>( p % 640 );
    } else {
        y = static_cast<float>( p % 640 );
        x = 0.0;
    }

    setVelocity(random_speed(engine),random_heading(engine),random_angular_velocity(engine));
    setPose(x,y,0);
    file_name = "../data/meteorBrown_big1.png";
    image_width = 101;
    image_height = 85;
}