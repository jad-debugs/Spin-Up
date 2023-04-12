#include "main.h"
#include "okapi/impl/device/rotarysensor/IMU.hpp"

okapi::Controller controller;
okapi::Rate rate;

pros::Optical opticalSensor = pros::Optical(opticalPort);


// okapi::IMU imu = IMU(imuPort, IMUAxes::y);

