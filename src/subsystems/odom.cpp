#include "main.h"
#include <cmath>

const double PI = 3.141592653589793238462643383279502884L;
#define toRadian(theta) (PI*theta)

const double WHEEL_RADIUS = 1.375;
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

// angle in degrees
void rotate(double targetAngle) {
    double kP = 0.01;
    double kI = 0.01;
    double kD = 0.03;

    double curAngle = 90 - imu.get();

    double error = targetAngle - curAngle;
    double integral = 0;
    double derivative = error;
    double prevError = 0;

    while (abs(error) <= 3) {
        curAngle = 90 - imu.get();
        error = targetAngle - curAngle;
        integral += error;
        derivative = error - prevError;

        double vel = error*kP + integral*kI + derivative*kD;

        drive -> getModel() -> arcade(0, vel);

        prevError = error;

        rate.delay(100_Hz);
    }

    drive -> getModel() -> arcade(0, 0);
}

// distance in inches
void driveForward(double distance) {
    double kP = 0.01;
    double kI = 0.01;
    double kD = 0.03;

    double orgDistance = sqrt(posX*posX + posY*posY);

    double error = distance;
    double integral = 0;
    double derivative = error;
    double prevError = 0;

    while (error >= 7) {
        double error = sqrt(posX*posX + posY*posY) - orgDistance;
        integral += error;
        derivative = error - prevError;

        double vel = error*kP + integral*kI + derivative*kD;
        vel = (vel > 11000 ? 11000 : vel);

        drive -> getModel() -> arcade(vel, 0);

        prevError = error;

        rate.delay(100_Hz);
    }

    drive -> getModel() -> arcade(0, 0);
}

void driveToPoint(double x, double y) {
    
}

