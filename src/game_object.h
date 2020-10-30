#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <vector>
#include <string>

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

    bool alive{true};

    float screen_height = 640;
    float screen_width = 640;

    std::string file_name;
    int image_height;
    int image_width;

protected:
    float maximum_speed_ = 10.0;
    float minimum_speed_ = 0.0;
    Pose pose_;
    Velocity velocity_;
};

#endif