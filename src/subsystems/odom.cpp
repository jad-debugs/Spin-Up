#include "main.h"
#include <cmath>
#include <string>

const double PI = 3.141592653589793238462643383279502884L;
#define toRadian(theta) (PI/180*theta)

const double WHEEL_RADIUS = 1.375;
// const double T_l = 2.5;
const double T_r = 4;
const double T_c = 2.75;

okapi::ADIEncoder leftEncoder = ADIEncoder(encoderLPort1, encoderLPort2, false);
okapi::ADIEncoder rightEncoder = ADIEncoder(encoderRPort1, encoderRPort2, true);
okapi::ADIEncoder centerEncoder = ADIEncoder(encoderCPort1, encoderCPort2, false);

double posX = 0;
double posY = 0;

double prevLeft = 0;
double prevRight = 0;
double prevCenter = 0;

int theta = 0;

double thetaPrev = 0;

bool isPressed = false;

void updateOdom() {
    // get rotations number of rotations to find distane each wheel travels
    double deltaLeft = (leftEncoder.get() - prevLeft)*PI/360 * 2*WHEEL_RADIUS;
    double deltaRight = (rightEncoder.get() - prevRight)*PI/360 * 2*WHEEL_RADIUS;
    double deltaCenter = (centerEncoder.get() - prevCenter)*PI/360 * 2*WHEEL_RADIUS;

    // double theta = toRadian(90 - imu.get());
    // double deltaTheta = theta - thetaPrev;
    double deltaTheta = (deltaLeft - deltaRight)/(T_r*2);
    theta += deltaTheta*180/pi;
    theta %= 360;

    // radius to center of bot
    double radiusY = deltaRight/deltaTheta + T_r;
    double radiusX = deltaCenter/deltaTheta + T_c;
    
    // chaning from polar to cartesian

    if (deltaTheta == 0) {
        posX = deltaCenter; // radius*cos(deltaTheta);
        posY = deltaRight; // radius*sin(deltaTheta);
    }
    else {
        posX = radiusX*sin(deltaTheta);
        posY = radiusY*sin(deltaTheta);
    }
    

    if (controller.getDigital(ControllerDigital::up) == 1) {
        pros::lcd::set_text(1, std::to_string(posX));
        pros::lcd::set_text(2, std::to_string(posY));
        pros::lcd::set_text(3, std::to_string(deltaTheta*180/PI));
    }

    double prevLeft = leftEncoder.get();
    double prevRight = rightEncoder.get();
    double prevBack = centerEncoder.get();
    // thetaPrev = theta;


}

// angle in degrees
void rotate(double targetAngle) {
    double kP = 0.01;
    double kI = 0.0;
    double kD = 0.03;

    targetAngle *= 180/PI;

    double curAngle = 0;

    double prevLeft1 = 0;
    double prevRight1 = 0;

    double deltaLeft = 0;
    double deltaRight = 0;
    double error = targetAngle - curAngle;
    double integral = 0;
    double derivative = error;
    double prevError = 0;

    while (abs(error) <= 0.052) {
        deltaLeft = (leftEncoder.get() - prevLeft1)*PI/360 * 2*WHEEL_RADIUS;
        deltaRight = (rightEncoder.get() - prevRight1)*PI/360 * 2*WHEEL_RADIUS; 
        curAngle += (deltaLeft - deltaRight)/(T_r*2);
        // curAngle = 90 - imu.get();
        error = targetAngle - curAngle;
        integral += error;
        derivative = error - prevError;

        double vel = error*kP + integral*kI + derivative*kD;

        drive -> getModel() -> tank(vel, 0);

        prevError = error;

        prevLeft1 = leftEncoder.get();
        prevRight1 = rightEncoder.get();

        rate.delay(100_Hz);
    }

    drive -> getModel() -> tank(0, 0);
}

// distance in inches
void driveForward(double distance) {
    double kP = 0.05;
    double kI = 0.0;
    double kD = 0.03;

    double orgPos = rightEncoder.get()*PI/360 * 2*WHEEL_RADIUS; 
    double error = distance;
    double integral = 0;
    double derivative = 0;
    double prevError = 0;

    while (error >= 2) {
        error =  distance - (rightEncoder.get()*PI/360 * 2*WHEEL_RADIUS - orgPos);
        integral += error;
        derivative = error - prevError;

        double vel = error*kP + integral*kI + derivative*kD;
        vel = (vel > 1 ? 0.98 : vel);

        drive -> getModel() -> tank(vel, vel);

        prevError = error;

        rate.delay(100_Hz);
    }

    drive -> getModel() -> tank(0, 0);
}

