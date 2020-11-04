#include "collision_detection.h"
#include "game_object.h"

bool CollisionDetection::detect_collision(const GameObject &game_object_1, const GameObject &game_object_2) {
  // check if image boxes over lap
  // https://www.geeksforgeeks.org/find-two-rectangles-overlap/
  if (game_object_1.getPose().x - game_object_1.getWidth()/2 >= game_object_2.getPose().x + game_object_2.getWidth()/2 ||
      game_object_2.getPose().x - game_object_2.getWidth()/2 >= game_object_1.getPose().x + game_object_1.getWidth()/2 ) {
    return false;
  }
  if (game_object_1.getPose().y + game_object_1.getHeight()/2 <= game_object_2.getPose().y - game_object_2.getHeight()/2 ||
      game_object_2.getPose().y + game_object_1.getHeight()/2 <= game_object_1.getPose().y - game_object_1.getHeight()/2 ) {
    return false;
  }
  return true;
}

bool CollisionDetection::detect_point_collision(const GameObject &game_object, float x, float y) {
  // check if point lies in image box
  // https://www.geeksforgeeks.org/check-if-a-point-lies-on-or-inside-a-rectangle-set-2/#:~:text=A%20point%20lies%20inside%20or,right%20and%20top%2Dleft%20coordinates.
  if (x <= game_object.getPose().x + game_object.getWidth()/2 &&
      x >= game_object.getPose().x - game_object.getWidth()/2 &&
      y >= game_object.getPose().y - game_object.getHeight()/2 &&
      y <= game_object.getPose().y + game_object.getHeight()/2) {
    return true;
  } else {
    return false;
  }
}