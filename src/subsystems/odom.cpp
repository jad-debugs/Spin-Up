#include "main.h"
#include "okapi/api/control/iterative/iterativePosPidController.hpp"
#include "okapi/impl/control/iterative/iterativeControllerFactory.hpp"
#include <cmath>
#include <string>

const double PI = 3.141592653589793238462643383279502884L;
#define toRadian(theta) (PI/180*theta)


const double WHEEL_RADIUS = 1.375;
// const double T_l = 2.5;
const double T_r = 3.75;
const double T_c = 1;

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

// void updateOdom() {
//     // get rotations number of rotations to find distane each wheel travels
//     double deltaLeft = (leftEncoder.get() - prevLeft)*PI/360 * 2*WHEEL_RADIUS;
//     double deltaRight = (rightEncoder.get() - prevRight)*PI/360 * 2*WHEEL_RADIUS;
//     double deltaCenter = (centerEncoder.get() - prevCenter)*PI/360 * 2*WHEEL_RADIUS;

//     // double theta = toRadian(90 - imu.get());
//     // double deltaTheta = theta - thetaPrev;
//     double deltaTheta = (drltaLeft - deltaRight)/(T_r*2);
//     theta += deltaTheta*180/pi;
//     theta %= 360;

//     // radius to center of bot
//     double radiusY = deltaRight/deltaTheta + T_r;
//     double radiusX = deltaCenter/deltaTheta + T_c;
    
//     // chaning from polar to cartesian

//     if (deltaTheta == 0) {
//         posX = deltaCenter; // radius*cos(deltaTheta);
//         posY = deltaRight; // radius*sin(deltaTheta);
//     }
//     else {
//         posX += radiusX*sin(deltaTheta);
//         posY += radiusY*sin(deltaTheta);
//     }
    

//     if (controller.getDigital(ControllerDigital::up) == 1) {
//         pros::lcd::set_text(4, std::to_string(posX));
//         pros::lcd::set_text(5, std::to_string(posY));
//         pros::lcd::set_text(6, std::to_string(theta));
//     }

//     double prevLeft = leftEncoder.get();
//     double prevRight = rightEncoder.get();
//     double prevBack = centerEncoder.get();
//     // thetaPrev = theta;


// }

// angle in degrees
void rotate(double targetAngle) {
    okapi::IterativePosPIDController rotatePID = okapi::IterativeControllerFactory::posPID(0.1, 0, 0.03);

    targetAngle *= 180/PI;

    double curAngle = drive->getState().theta.convert(okapi::degree);


    while (abs(targetAngle - curAngle) >= 3) {
        curAngle = drive->getState().theta.convert(okapi::degree);

        double vel = rotatePID.step(curAngle);

        drive -> getModel() -> tank(vel, -vel);

        rate.delay(100_Hz);
    }

    rotatePID.reset();
    drive -> getModel() -> tank(0, 0);
}

// distance in inches
void driveForward(double distance) {
    okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0.1, 0, 0.01);

    const double target = distance;

    drivePID.setTarget(target);

    double orgPosX = drive->getState().x.convert(okapi::foot);
    double orgPosY = drive->getState().y.convert(okapi::foot);

    double distTravelled = 69696.420;

    while (abs(target-distTravelled) >= 0.25) {
        double dx = drive->getState().x.convert(okapi::foot) - orgPosX;
        double dy = drive->getState().y.convert(okapi::foot) - orgPosY;

        pros::lcd::set_text(1, std::to_string(drive->getState().x.convert(okapi::inch)));
        pros::lcd::set_text(2, std::to_string(drive->getState().y.convert(okapi::inch)));
        
        distTravelled = sqrt(dx*dx + dy*dy);
        
        double vel = drivePID.step(distTravelled);

        drive -> getModel() -> tank(vel, vel);

        rate.delay(100_Hz);
    }

    drivePID.reset();
    drive -> getModel() -> tank(0, 0);
}

