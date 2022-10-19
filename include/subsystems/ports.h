#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"
#include "okapi/impl/device/rotarysensor/potentiometer.hpp"
#include <chrono>

using namespace okapi;

// big boy d-train ports
const std::uint8_t rightFrontPort = 13;
const std::uint8_t rightTopPort = 4;
const std::uint8_t rightBottomPort = 5;

const std::uint8_t leftFrontPort = 11;
const std::uint8_t leftTopPort = 19;
const std::uint8_t leftBottomPort = 18;

// conveyor/intake sucky sucky port
const std::uint8_t conveyorPort = 9;

// flywheel shooty port
const std::uint8_t flywheelPort = 10;

// sensors later
const std::uint8_t encoderLPort1 = 'A';
const std::uint8_t encoderLPort2 = 'B';
const std::uint8_t encoderRPort1 = 'C';
const std::uint8_t encoderRPort2 = 'D';
const std::uint8_t encoderCPort1 = 'E';
const std::uint8_t encoderCPort2 = 'F';
const std::uint8_t visionSensorPort = 'G'; // 8

const std::uint8_t imuPort = 20;

// pnuematics if we use
const std::uint8_t indexerPort = 'H';



