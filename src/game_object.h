#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>

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
        float angular_velocity = 0.0;
    };
    
    void setPose(float x, float y, float angle);
    Pose getPose() const {return pose_;}
    void setVelocity(float velocity, float angular_velocity);
    Velocity getVelocity() const {return velocity_;}
    void setDirection(float angle);
    std::vector<float> getDirection() const {return direction_;}
    void updatePose();

    float screen_height;
    float screen_width;

protected:
    float maximum_speed_ = 10.0;
    float minimum_speed_ = 0.0;
    std::vector<float> direction_ = {0.0, 1.0};
    Pose pose_;
    Velocity velocity_;
};

#endif