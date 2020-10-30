#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "game_object.h"

namespace CollisionDetection {

bool detect_collision(const GameObject &game_object_1, const GameObject &game_object_2);

}; // CollisionDetection
#endif