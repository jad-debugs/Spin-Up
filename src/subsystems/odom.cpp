#include "main.h"
#include <cmath>

const double PI = 3.141592653589793238462643383279502884L;
#define toRadian(theta) (PI*theta)

const double WHEEL_RADIUS = 2.0;
// const double T_l = 2.5;
const double T_r = 2.5;
// const double T_b = 2.75;



double posX = 0;
double posY = 0;

// double prevLeft = 0;
double prevRight = 0;
double prevCenter = 0;

double thetaPrev = 0;

void updateOdom() {
    // get rotations number of rotations to find distane each wheel travels
    // double deltaLeft = toRadian((leftEncoder.get() - prevLeft) * WHEEL_RADIUS);
    double deltaRight = toRadian((rightEncoder.get() - prevRight) * WHEEL_RADIUS);
    double deltaCenter = toRadian((centerEncoder.get() - prevCenter) * WHEEL_RADIUS);

    double theta = toRadian(90 - imu.get());
    double deltaTheta = theta - thetaPrev;

    // radius to center of bot
    double radius = deltaRight/deltaTheta + T_r;

    // chaning from polar to cartesian
    posX += radius*cos(theta);
    posY += radius*sin(theta);

    // double prevLeft = leftEncoder.get();
    double prevRight = rightEncoder.get();
    double prevBack = centerEncoder.get();
    thetaPrev = theta;
}

void rotate(double targetAngle) {
    
}

