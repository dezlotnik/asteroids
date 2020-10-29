#include "asteroid.h"

Asteroid::Asteroid() :
    engine(dev()),
    random_x(0, static_cast<float>(640)),
    random_y(0, static_cast<float>(640)),
    random_heading(0, static_cast<float>(360)),
    random_speed(2, static_cast<float>(5))
{
    setVelocity(random_speed(engine),random_heading(engine),3);
    setPose(random_x(engine),random_y(engine),0);
}