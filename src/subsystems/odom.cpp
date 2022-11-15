#include "main.h"
#include "okapi/api/control/iterative/iterativePosPidController.hpp"
#include "okapi/impl/control/iterative/iterativeControllerFactory.hpp"
#include <cmath>
#include <iterator>
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
IMU imu(imuPort, IMUAxes::z);

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
    okapi::IterativePosPIDController rotatePID = okapi::IterativeControllerFactory::posPID(0.015, 0, 0.0001);
    
    rotatePID.setTarget(targetAngle);

    // double curAngle = drive->getState().theta.convert(okapi::degree);
    double curAngle = imu.controllerGet();

    while (abs(targetAngle - curAngle) >= 3) {
        // curAngle = drive->getState().theta.convert(okapi::degree);
        curAngle = imu.controllerGet();

        double vel = rotatePID.step(curAngle);

        drive -> getModel() -> tank(vel, -vel);

        pros::delay(20);
    }
    
    rotatePID.reset();

    // leftFront.setBrakeMode(AbstractMotor::brakeMode::hold);
    // leftTop.setBrakeMode(AbstractMotor::brakeMode::hold);
    // leftBottom.setBrakeMode(AbstractMotor::brakeMode::hold);

    // rightFront.setBrakeMode(AbstractMotor::brakeMode::hold);
    // rightTop.setBrakeMode(AbstractMotor::brakeMode::hold);
    // rightBottom.setBrakeMode(AbstractMotor::brakeMode::hold);

    drive -> getModel() -> tank(0, 0);

    // pros::delay(1000);
    
    // leftFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    // leftTop.setBrakeMode(AbstractMotor::brakeMode::coast);
    // leftBottom.setBrakeMode(AbstractMotor::brakeMode::coast);

    // rightFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    // rightTop.setBrakeMode(AbstractMotor::brakeMode::coast);
    // rightBottom.setBrakeMode(AbstractMotor::brakeMode::coast);
}

// distance in inches
void driveForward(double distance) {
    okapi::IterativePosPIDController drivePID = okapi::IterativeControllerFactory::posPID(0.75, 0, 0.001);

    const double target = distance;

    drivePID.setTarget(target);

    double orgPosX = drive->getState().x.convert(okapi::foot);
    double orgPosY = drive->getState().y.convert(okapi::foot);

    double distTravelled = 69696.420;

    while (abs(target-distTravelled) >= 0.2) {
        double dx = drive->getState().x.convert(okapi::foot) - orgPosX;
        double dy = drive->getState().y.convert(okapi::foot) - orgPosY;

        distTravelled = sqrt(dx*dx + dy*dy);
        
        double vel = drivePID.step(distTravelled);

        drive -> getModel() -> tank(vel, vel);

        pros::delay(10);
    }

    drivePID.reset();
    drive -> getModel() -> tank(0, 0);
}

