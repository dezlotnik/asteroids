cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(Asteroids src/main.cpp src/renderer.cpp src/controller.cpp src/game.cpp src/spaceship.cpp src/game_object.cpp src/asteroid.cpp src/laser.cpp src/collision_detection.cpp src/enemy.cpp)

target_link_libraries(Asteroids ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})