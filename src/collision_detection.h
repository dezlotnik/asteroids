#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H

#include "game_object.h"

namespace CollisionDetection {

bool detect_collision(const GameObject &game_object_1, const GameObject &game_object_2);

bool detect_point_collision(const GameObject &game_object, float x, float y);


}; // CollisionDetection
#endif