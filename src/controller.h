#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "car.h"

class Game; // Forward declaration

class Controller {
 public:
  void HandleInput(bool &running, Car &car, Game &game) const;

 private:
};

#endif
