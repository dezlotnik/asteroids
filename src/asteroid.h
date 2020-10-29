#ifndef ASTEROID_H
#define ASTEROID_H

#include "game_object.h"

class Asteroid : public GameObject {
public:
    Asteroid();
    void Update() {updatePose();}
private:
};

#endif