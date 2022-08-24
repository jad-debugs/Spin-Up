#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/potentiometer.hpp"

using namespace okapi;

// big boy d-train ports
const std::uint8_t rightFrontPort = 6;
const std::uint8_t rightTopPort = 4;
const std::uint8_t rightBottomPort = 5;

const std::uint8_t leftFrontPort = 12;
const std::uint8_t leftTopPort = 19;
const std::uint8_t leftBottomPort = 20;

// conveyor/intake sucky sucky port
const std::uint8_t conveyorIntakePort = 9;

// flywheel shooty port
const std::uint8_t flywheelPort = 10;

// sensors later
// const std::uint8_t encoderLPort = 1;
// const std::uint8_t encoderRPort = 2;
// const std::uint8_t encoderCPort = 3;

// const std::uint8_t imuPort = 4;

// pnuematics if we use
const std::uint8_t indexerPort = 'H';