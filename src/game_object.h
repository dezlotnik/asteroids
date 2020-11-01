#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "asteroid_constants.h"
#include <vector>
#include <string>

using namespace AsteroidConstants;

class GameObject {
public:
    GameObject() {}
    struct Pose {
        float x = 0.0;
        float y = 0.0;
        float yaw = 0.0;
    };
    struct Velocity {
        float velocity = 0.0;
        float heading = 0.0;
        float angular_velocity = 0.0;
    };
    
    void setPose(float x, float y, float yaw);
    Pose getPose() const {return pose_;}
    void setVelocity(float velocity, float heading, float angular_velocity);
    Velocity getVelocity() const {return velocity_;}
    void updatePose();
    virtual float getMaximumSpeed() {return maximum_speed_;}
    virtual float getMinimumSpeed() {return minimum_speed_;}
    std::string getImageName() const {return image_name_;}
    float getHeight() const {return height_;}
    float getWidth() const {return width_;}
    void setImageName(std::string name) {image_name_ = name;}
    void setHeight(float height) {height_ = height;}
    void setWidth(float width) {width_ = width;}
    bool isAlive() const {return alive_;}
    virtual void kill() {alive_ = false;}

protected:
    float maximum_speed_ = 10.0;
    float minimum_speed_ = 0.0;
    Pose pose_;
    Velocity velocity_;
    std::string image_name_;
    int height_;
    int width_;
    bool alive_ = true;
};

#endif