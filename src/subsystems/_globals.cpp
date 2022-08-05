#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"

okapi::Controller controller;
okapi::Rate rate;

okapi::ADIEncoder leftEncoder = ADIEncoder({encoderLPort, 'A', 'B'}, false);
// okapi::ADIEncoder rightEncoder = ADIEncoder({encoderRPort, 'A', 'B'}, false);
okapi::ADIEncoder centerEncoder = ADIEncoder({encoderCPort, 'A', 'B'}, false);

okapi::IMU imu = IMU(imuPort, IMUAxes::y);

Motor conveyorIntake(conveyorIntakePort, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);
