#include "game_object.h"
#include <math.h>

void GameObject::setPose(float x, float y, float angle) {
    pose_.x = x;
    pose_.y = y;
    pose_.angle = angle;
}

void GameObject::setVelocity(float velocity, float heading, float angular_velocity) {
    if (velocity > maximum_speed_) {
        velocity_.velocity = maximum_speed_;
    } else if (velocity < minimum_speed_) {
        velocity_.velocity = minimum_speed_;
    } else {
        velocity_.velocity = velocity;
    }
    velocity_.heading = heading;
    velocity_.angular_velocity = angular_velocity;
}

void GameObject::updatePose() {
    pose_.x -= cos((velocity_.heading + 90.0) * 3.14/180.0) * velocity_.velocity;
    pose_.y -= sin((velocity_.heading + 90.0) * 3.14/180.0) * velocity_.velocity;
    pose_.angle += velocity_.angular_velocity;
    
    pose_.x = fmod(pose_.x + screen_width, screen_width);
    pose_.y = fmod(pose_.y + screen_height, screen_height);
}