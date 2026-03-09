#ifndef PARKING_CONSTANTS_H
#define PARKING_CONSTANTS_H

#include <cstddef>

namespace ParkingConstants {

constexpr std::size_t kFramesPerSecond{60};
constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
constexpr std::size_t kScreenWidth{800}; // Adjusted for better car visualization
constexpr std::size_t kScreenHeight{600};

} //ParkingConstants 

#endif
