#include <iostream>
#include "parking_constants.h"
#include "renderer.h"
#include "controller.h"
#include "game.h"

using namespace ParkingConstants;

int main() {

  Renderer renderer(kScreenWidth, kScreenHeight);
  Controller controller;
  Game game(kScreenWidth, kScreenHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Parking Simulator terminated successfully!\n";

  return 0;
}
