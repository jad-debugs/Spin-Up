#include "main.h"

using namespace okapi;

// roller
drive->getModel()->setBrakeMode(AbstractMotor::brakeMode{2});

drive->getModel()->tank(.2, .2);

pros::Motor conveyor(9);
conveyor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
conveyor.move_relative(720, 600);


pros::delay(20);

rotate(90);
driveForward(3, true);
rotate(70);

int cnt = 0;

while (cnt < 2) {
    double kP = 0.03;
    double ki = 0.0;
    double kd = 0.1;

    int error = 450-flywheel.getActualVelocity();
    int integral = integral + error;
    int derivative = error - prevError;
    int prevError = error;
    int p = error * kP;
    int i = integral * ki;
    int d = derivative * kd;

    flywheel.moveVelocity(500+p+i+d);

    if (error - 25 <= 0 || error + 25 >= 0) {
        indexer.set_value(false);
        pros::delay(700);
        indexer.set_value(true);
        cnt++;
    }

    rate.delay(10);
}

cnt = 0;

// rotate(65);


