# ASTEROIDS!

An SDL game based on the classic Asteroids arcade game. Defeat enemy spaceships
and blast away dangerous asteroids. 

* Press <kbd>SPACE</kbd> to fire lasers.
* Press <kbd>↑</kbd> to accelerate.
* Press <kbd>←</kbd> to turn left.
* Press <kbd>→</kbd> to turn right.

Completed as part of Udacity's C++ Nanodegree Program.

Credit [Kenney](https://kenney.nl) for game artwork.

<img src="asteroids.gif"/>

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2_image >= 2.0
  * All installation instructions can be found [here](https://www.libsdl.org/projects/SDL_image/)
  * For Linux, install via `sudo apt-get install libsdl2-image-dev`.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./Asteroids`.

## File and Class Structure
* `main.cpp`
  * Starts the game loop.
* `game.cpp/h`
  * Definition of the `Game` class that updates the game state.
* `renderer.cpp/h`
  * Definition of the `Renderer` class that renders game objects to the screen.
* `controller.cpp/h`
  * Definition of the `Controller` class that handles keyboard inputs.
* `game_object.cpp/h`
  * Definition of the `GameObject` base class that encapsulates data for objects
  that interact with the game loop and are rendered to the screen.
* `asteroids.cpp/h`
  * Definition of the `Asteroid` class derived from `GameObject` that defines the 
  behavior of asteroids. 
* `ship.cpp/h`
  * Definition of the `Ship` class derived from `GameObject` that defines the
  behavior of spaceships.
* `spacecraft.cpp/h`
  * Definition of the `Spacecraft` class derived from `Ship` that defines the
  behavior of the player spaceship.
* `enemy.cpp/h`
  * Definition of the `Enemy` class derived from `Ship` that defines the
  behavior of the enemy spaceships.
* `laser.cpp/h`
  * Definition of the `Laser` class derived from `GameObject` that defines the
  behavior of the lasers that are fired from spaceships.
* `collision_detection.cpp/h`
  * Helper functions for detecting collisions between game objects.
* `asteroid_constants.h`
  * Defines constants used throughout the program.

## Capstone Project Rubric
* The project demonstrates an understanding of C++ functions and control structures.
  * Used throughout the program. 
* The project reads data from a file and process the data, or the program writes data to a file.
  * Levels are loaded from the `data/levels.txt` file in `game.cpp` line `16`.
* The project uses Object Oriented Programming techniques.
  * Used throughout the program. For example, `ship.cpp/h`. 
* Class constructors utilize member initialization lists.
  * Initialization lists are used when appropriate. See for example 
  `asteroids.cpp` line `12`.
* Classes encapsulate behavior.
  * The `GameObject` class encapsulates data and functions associated with 
  game objects. For example, the position and orientation of a game object is 
  stored in the `pose_` member variable of `GameObject`. Pose data is manipulated
  in the `setPose` method of `GameObject`. The pose is updated based on the
  object velocity via the `updatePose` method.
  * Invariants are used in the `setVelocity` method of `GameObject` in `game_object.cpp` line `12`.
* Classes follow an appropriate inheritance hierarchy.
  * `SpaceShip` and `Enemy` inherit from `Ship`, which inherits from `GameObject`.
  * Composition is used. The `SpaceShip` class has a member `lasers` which is 
  a vector of `Laser` unique pointers.
  * Override functions are specified. See `ship.h` line `28`.
* Derived class functions override virtual base class functions.
  * See `ship.h` line `28`.
* The project makes use of references in function declarations.
  * See `renderer.h` line `16`.
  * See `collision_detection.h` line `8`.
* The project uses smart pointers instead of raw pointers.
  * Enemy and asteroid objects are stored in a vector of unique pointers in
  `game.h` lines `29` and `30`.
  * Spaceship lasers are stored as a vector of unique pointers in `ship.h` line
  `12`.