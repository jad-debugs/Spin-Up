#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/potentiometer.hpp"
#include <chrono>

using namespace okapi;

// big boy d-train ports
const std::uint8_t rightFrontPort = 2;
const std::uint8_t rightTopPort = 15;
const std::uint8_t rightBottomPort = 1;

const std::uint8_t leftFrontPort = 3;
const std::uint8_t leftTopPort = 19;
const std::uint8_t leftBottomPort = 4;

// conveyor/intake sucky sucky port
const std::uint8_t conveyorPort = 9;

// flywheel shooty port
const std::uint8_t flywheelPort = 7;

// sensors later
const std::uint8_t encoderLPort1 = 'H';
const std::uint8_t encoderLPort2 = 'G';
const std::uint8_t encoderRPort1 = 'A';
const std::uint8_t encoderRPort2 = 'B';
const std::uint8_t encoderCPort1 = 'E';
const std::uint8_t encoderCPort2 = 'F';
const std::uint8_t visionSensorPort = 'G'; // 8

const std::uint8_t imuPort = 11;

// pnuematics if we use
const std::uint8_t indexerPort = 'H';


