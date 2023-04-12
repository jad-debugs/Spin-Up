#include "main.h"

extern okapi::IterativePosPIDController drivePID;
extern okapi::IMU imu;

void updateOdom();
void driveForward(double distance, bool backwards=false);
void rotate(double angle);

void rollUntilColor(int color);