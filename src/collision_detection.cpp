#include "collision_detection.h"
#include "game_object.h"

bool CollisionDetection::detect_collision(const GameObject &game_object_1, const GameObject &game_object_2) {
    if (game_object_1.getPose().x >= game_object_2.getPose().x + game_object_2.image_width || 
        game_object_2.getPose().x >= game_object_1.getPose().x + game_object_1.image_width ) {
        return false;
    }
    if (game_object_1.getPose().y <= game_object_2.getPose().y - game_object_2.image_height || 
        game_object_2.getPose().y <= game_object_1.getPose().y - game_object_1.image_height ) {
        return false;
    }
    return true;
}