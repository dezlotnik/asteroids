#include "game_object.h"
#include <math.h>

void GameObject::setPose(float x, float y, float angle) {
    pose_.x = x;
    pose_.y = y;
    pose_.angle = angle;
}

void GameObject::setVelocity(float velocity, float angular_velocity) {
    velocity_.velocity = velocity;
    velocity_.angular_velocity = angular_velocity;
}

void GameObject::setDirection(float angle) {
    direction_[0] = cos(angle * 3.14/180.0);
    direction_[1] = sin(angle * 3.14/180.0);
}

void GameObject::updatePose() {
    pose_.x -= cos((pose_.angle + 90.0) * 3.14/180.0) * velocity_.velocity;
    pose_.y -= sin((pose_.angle + 90.0) * 3.14/180.0) * velocity_.velocity;
    pose_.angle += velocity_.angular_velocity;
    
    pose_.x = fmod(pose_.x + screen_width, screen_width);
    pose_.y = fmod(pose_.y + screen_height, screen_height);
}