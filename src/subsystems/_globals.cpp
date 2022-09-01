#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"

okapi::Controller controller;
okapi::Rate rate;

okapi::ADIEncoder leftEncoder = ADIEncoder(encoderLPort1, encoderLPort2, false);
okapi::ADIEncoder rightEncoder = ADIEncoder(encoderRPort1, encoderRPort2, false);
okapi::ADIEncoder centerEncoder = ADIEncoder(encoderCPort1, encoderCPort2, false);

// okapi::IMU imu = IMU(imuPort, IMUAxes::y);

