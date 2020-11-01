#ifndef ASTEROID_CONSTANTS_H
#define ASTEROID_CONSTANTS_H

#include <cstddef>

namespace AsteroidConstants {

constexpr std::size_t kFramesPerSecond{60};
constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
constexpr std::size_t kScreenWidth{1280};
constexpr std::size_t kScreenHeight{640};

} //AsteroidConstants 

#endif