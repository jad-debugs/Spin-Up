#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
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
const std::uint8_t encoderLPort = 1;
const std::uint8_t encoderRPort = 2;
const std::uint8_t encoderCPort = 3;

const std::uint8_t imuPort = 4;

// pnuematics if we use