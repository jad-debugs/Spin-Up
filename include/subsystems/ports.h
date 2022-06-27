#include "main.h"
#include "okapi/impl/device/rotarysensor/potentiometer.hpp"

using namespace okapi;

// big boy d-train ports
const std::uint8_t rightFrontPort = 4;
const std::uint8_t rightTopPort = 5;
const std::uint8_t rightBottomPort = 6;

const std::uint8_t leftFrontPort = 1;
const std::uint8_t leftTopPort = 2;
const std::uint8_t leftBottomPort = 3;

// conveyor sucky sucky port
const std::uint8_t conveyorPort = 69;

// flywheel shooty port
const std::uint8_t flywheelPort = 42;

// sensors later
const std::uint8_t potentPort1 = 1;
const std::uint8_t potentPort2 = 2;
const std::uint8_t potentPort3 = 3;
const std::uint8_t imuPort = 6;

// pnuematics if we use