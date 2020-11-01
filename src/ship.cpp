
#include "ship.h"
#include "laser.h"

void Ship::Fire() {
    if (lasers.empty()) {
        lasers.push_back(std::make_shared<Laser>((*this)));
    } else if (lasers.back()->getDistance() > reload_distance) {
        lasers.push_back(std::make_shared<Laser>(*this));
    }
}

void Ship::updateLasers() {
    if (!lasers.empty()) {
        auto it = lasers.begin();
        while (it != lasers.end()) {
            std::shared_ptr<Laser> &laser = *it;
            laser->Update();
            if (laser->getDistance() < laser->getRange() && laser->isAlive()) {
                ++it;
            } else {
                it = lasers.erase(it);
            }
        }
    }
}