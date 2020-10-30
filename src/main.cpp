#include <iostream>
#include "asteroid_constants.h"
#include "renderer.h"
#include "controller.h"
#include "game.h"

using namespace AsteroidConstants;

int main() {

    Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    Game game(kScreenWidth, kScreenHeight);
    game.Run(controller, renderer, kMsPerFrame);
    std::cout << "Game has terminated successfully!\n";
    std::cout << "Score: " << game.GetScore() << "\n";

    return 0;
}