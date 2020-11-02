
#include "ship.h"
#include "laser.h"

void Ship::Fire() {
    if (lasers.empty()) {
        lasers.push_back(std::make_unique<Laser>((*this)));
    } else if (lasers.back()->getDistance() > reload_distance_) {
        lasers.push_back(std::make_unique<Laser>(*this));
    }
}

void Ship::updateLasers() {
    if (!lasers.empty()) {
        auto it = lasers.begin();
        while (it != lasers.end()) {
            std::unique_ptr<Laser> &laser = *it;
            laser->Update();
            if (laser->getDistance() < laser->getRange() && laser->isAlive()) {
                ++it;
            } else {
                it = lasers.erase(it);
            }
        }
    }
}

void Ship::propagateState(float acceleration, float angular_velocity) {
    float speed = velocity_.velocity;
    float heading = velocity_.heading;
    float vx = speed*cos(heading*3.14/180.0);
    float vy = speed*sin(heading*3.14/180.0);
    vx += acceleration*cos(pose_.yaw*3.14/180.0);
    vy += acceleration*sin(pose_.yaw*3.14/180.0);
    speed = sqrt(vx*vx + vy*vy);
    heading = 180.0/3.14*atan2(vy,vx);
    
    setVelocity(speed,heading,angular_velocity);
    updatePose();
}