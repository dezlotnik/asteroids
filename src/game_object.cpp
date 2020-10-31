#include <math.h>
#include "game_object.h"
#include "asteroid_constants.h"

using namespace AsteroidConstants;

void GameObject::setPose(float x, float y, float angle) {
    pose_.x = x;
    pose_.y = y;
    pose_.angle = angle;
}

void GameObject::setVelocity(float velocity, float heading, float angular_velocity) {
    if (velocity > getMaximumSpeed()) {
        velocity_.velocity = getMaximumSpeed();
    } else if (velocity < getMinimumSpeed()) {
        velocity_.velocity = getMinimumSpeed();
    } else {
        velocity_.velocity = velocity;
    }
    velocity_.heading = heading;
    velocity_.angular_velocity = angular_velocity;
}

void GameObject::updatePose() {
    pose_.x += cos((velocity_.heading) * 3.14/180.0) * velocity_.velocity;
    pose_.y += sin((velocity_.heading) * 3.14/180.0) * velocity_.velocity;
    pose_.angle += velocity_.angular_velocity;
    
    pose_.x = fmod(pose_.x + kScreenWidth, kScreenWidth);
    pose_.y = fmod(pose_.y + kScreenHeight, kScreenHeight);
}