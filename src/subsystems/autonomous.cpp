// #include "main.h"

// using namespace okapi;

// // roller
// drive->getModel()->setBrakeMode(AbstractMotor::brakeMode{2});

// drive->getModel()->tank(.2, .2);

// pros::Motor conveyor(9);
// conveyor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
// conveyor.move_relative(720, 600);


// pros::delay(20);

// rotate(90);
// driveForward(3, true);
// rotate(70);

// int cnt = 0;

// void flywheelTBHControl() {
//     float drive = 0;
//     float driveAtZero = 0;
//     float previousError = 0;
//     bool firstZeroCross = true;
//     while (true) {
//         float flywheelTargetRPM = static_cast<int>(currentFlywheelState);
//         float error = flywheelTargetRPM - (flywheelMotorGroup.getActualVelocity() * FLYWHEEL_GEAR_RATIO);
//         drive += error * FW_TBH_GAIN;
//         if (drive > 1) {
//             drive = 1;
//         } else if (drive < 0) {
//             drive = 0;
//         }
//         if (squiggles::sgn(error) != squiggles::sgn(previousError)) {
//             if (firstZeroCross) {
//                 drive = flywheelTargetRPM * FW_VOLTAGE_CONSTANT;
//                 firstZeroCross = false;
//             } else {
//                 drive = 0.5f * (drive + driveAtZero);
//             }
//             driveAtZero = drive;
//         }
//         previousError = error;

//         flywheelMotorGroup.moveVoltage(drive * 12000.0f);
//         pros::delay(10);
//     }
// }

// cnt = 0;

// // rotate(65);


