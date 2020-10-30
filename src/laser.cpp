#include "laser.h"
#include "spaceship.h"

Laser::Laser(const SpaceShip &spaceship) {
    file_name = "../data/laserBlue01.png";
    image_height = 54;
    image_width = 9;

    // set laser pose
    float x = 0;
    float y = -0.5*spaceship.image_height - 0.5*image_height;
    float angle = spaceship.getPose().angle * 3.14/180.0;
    float xp = cos(angle)*x - sin(angle)*y;
    float yp = sin(angle)*x + cos(angle)*y;
    setPose(spaceship.getPose().x + xp, spaceship.getPose().y + yp, spaceship.getPose().angle);

    // set laser velocity
    setVelocity(laser_speed_, spaceship.getPose().angle, 0);
}