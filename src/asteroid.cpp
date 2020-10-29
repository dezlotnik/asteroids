#include "asteroid.h"

Asteroid::Asteroid() :
    engine(dev()),
    random_x(0, static_cast<float>(640)),
    random_y(0, static_cast<float>(640)),
    random_angle(0, static_cast<float>(360)),
    random_speed(2, static_cast<float>(5))
{
    setVelocity(random_speed(engine),0);
    setPose(random_x(engine),random_y(engine),random_angle(engine));
}