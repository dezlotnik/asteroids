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
        float angle = 0.0;
    };
    struct Velocity {
        float velocity = 0.0;
        float heading = 0.0;
        float angular_velocity = 0.0;
    };
    
    void setPose(float x, float y, float angle);
    Pose getPose() const {return pose_;}
    void setVelocity(float velocity, float heading, float angular_velocity);
    Velocity getVelocity() const {return velocity_;}
    void setDirection(float angle);
    void updatePose();
    virtual float getMaximumSpeed() {return maximum_speed_;}
    virtual float getMinimumSpeed() {return minimum_speed_;}
    std::string getFileName() const {return file_name;}

    bool alive{true};

    float screen_height = kScreenHeight;
    float screen_width = kScreenWidth;

    std::string file_name;
    int image_height;
    int image_width;

protected:
    float maximum_speed_ = 10.0;
    float minimum_speed_ = 0.0;
    Pose pose_;
    Velocity velocity_;
};

class Ship : public GameObject {
public:
    std::string laser_file_name = "";
    float laser_range;
    float laser_speed;
};

#endif