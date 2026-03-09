cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(ParkingSim)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# Allow user to specify paths if they are in non-standard locations
# e.g. cmake .. -DSDL2_DIR=/path/to/sdl2 -DSDL2_IMAGE_DIR=/path/to/sdl2_image
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

include_directories(src ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(ParkingSim 
    src/main.cpp 
    src/renderer.cpp 
    src/controller.cpp 
    src/game.cpp 
    src/car.cpp 
    src/game_object.cpp 
    src/collision_detection.cpp
)

target_link_libraries(ParkingSim ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})
