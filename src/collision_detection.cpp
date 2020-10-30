#include "collision_detection.h"
#include "game_object.h"

bool CollisionDetection::detect_collision(const GameObject &game_object_1, const GameObject &game_object_2) {
    // check if image boxes over lap
    // https://www.geeksforgeeks.org/find-two-rectangles-overlap/
    if (game_object_1.getPose().x - game_object_1.image_width/2 >= game_object_2.getPose().x + game_object_2.image_width/2 ||
        game_object_2.getPose().x - game_object_2.image_width/2 >= game_object_1.getPose().x + game_object_1.image_width/2 ) {
        return false;
    }
    if (game_object_1.getPose().y + game_object_1.image_height/2 <= game_object_2.getPose().y - game_object_2.image_height/2 ||
        game_object_2.getPose().y + game_object_1.image_height/2 <= game_object_1.getPose().y - game_object_1.image_height/2 ) {
        return false;
    }
    return true;
}