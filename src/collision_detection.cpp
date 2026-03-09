#include "collision_detection.h"
#include "game_object.h"
#include <vector>
#include <utility>
#include <cstddef>
#include <algorithm>

bool CollisionDetection::detect_collision(const GameObject &game_object_1, const GameObject &game_object_2) {
  auto corners1 = game_object_1.getCorners();
  auto corners2 = game_object_2.getCorners();

  auto get_axes = [](const std::vector<GameObject::Point>& corners) {
    std::vector<GameObject::Point> axes;
    for (size_t i = 0; i < corners.size(); i++) {
      auto p1 = corners[i];
      auto p2 = corners[(i + 1) % corners.size()];
      auto edge = GameObject::Point{p2.x - p1.x, p2.y - p1.y};
      // Normal: (-y, x)
      axes.push_back({-edge.y, edge.x});
    }
    return axes;
  };

  auto axes1 = get_axes(corners1);
  auto axes2 = get_axes(corners2);

  std::vector<GameObject::Point> all_axes = axes1;
  all_axes.insert(all_axes.end(), axes2.begin(), axes2.end());

  for (const auto& axis : all_axes) {
    auto project = [](const std::vector<GameObject::Point>& corners, GameObject::Point axis) {
      float min = (corners[0].x * axis.x + corners[0].y * axis.y);
      float max = min;
      for (size_t i = 1; i < corners.size(); i++) {
        float p = (corners[i].x * axis.x + corners[i].y * axis.y);
        if (p < min) min = p;
        if (p > max) max = p;
      }
      return std::make_pair(min, max);
    };

    auto proj1 = project(corners1, axis);
    auto proj2 = project(corners2, axis);

    if (proj1.second < proj2.first || proj2.second < proj1.first) {
      return false; // Gap found
    }
  }

  return true;
}

bool CollisionDetection::detect_point_collision(const GameObject &game_object, float x, float y) {
  // check if point lies in image box
  // https://www.geeksforgeeks.org/check-if-a-point-lies-on-or-inside-a-rectangle-set-2/#:~:text=A%20point%20lies%20inside%20or,right%20and%20top%2Dleft%20coordinates.
  if (x <= game_object.getPose().x + game_object.getWidth() / 2 &&
      x >= game_object.getPose().x - game_object.getWidth() / 2 &&
      y >= game_object.getPose().y - game_object.getHeight() / 2 &&
      y <= game_object.getPose().y + game_object.getHeight() / 2) {
    return true;
  } else {
    return false;
  }
}