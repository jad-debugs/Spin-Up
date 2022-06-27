#include "main.h"
#include "okapi/impl/device/rotarysensor/potentiometer.hpp"

using namespace okapi;

extern Motor rightFront;
extern Motor rightTop;
extern Motor rightBottom;

extern Motor leftFront;
extern Motor leftTop;
extern Motor leftBottom;

extern IMU imu;
extern Potentiometer potent1;
extern Potentiometer potent1;
extern Potentiometer potent1;

extern std::shared_ptr<ChassisController> drive;

void updateDrive();
