#include "main.h"

using namespace okapi;

Motor rightFront(rightFrontPort, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightTop(rightTopPort, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor rightBottom(rightBottomPort, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

Motor leftFront(leftFrontPort, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftTop(leftTopPort, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);
Motor leftBottom(leftBottomPort, true, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::degrees);

// std::shared_ptr<ChassisController> drive =
//   ChassisControllerBuilder()
//   .withMotors({leftFront, leftTop, leftBottom}, {rightFront, rightTop, rightBottom})
//   .withDimensions(AbstractMotor::gearset::blue, {{4_in, 13.7_in}, imev5BlueTPR})
//   .build();

  std::shared_ptr<OdomChassisController> drive = 
    ChassisControllerBuilder()
    .withMotors({leftFront, leftTop, leftBottom}, {rightFront, rightTop, rightBottom})
    .withDimensions(AbstractMotor::gearset::blue, {{4_in, 13.7_in}, imev5BlueTPR})
    // .withSensors(
    //     ADIEncoder{encoderLPort1, encoderLPort2}, // Left encoder
    //     ADIEncoder{encoderRPort1, encoderRPort2},  // Right encoder
    //     ADIEncoder{encoderCPort1, encoderCPort2, true}  // Center encoder reversed
    // )
    // Specify the tracking wheels diam (2.75 in), track (7 in), and TPR (360)
    .withOdometry({{2.75_in, 6_in, 1_in, 2.75_in}, quadEncoderTPR})
    .buildOdometry();

void updateDrive() {
  drive -> getModel() -> tank(controller.getAnalog(ControllerAnalog::leftY), controller.getAnalog(ControllerAnalog::rightY));

  if (controller.getDigital(ControllerDigital::left) == 1) {
    leftFront.setBrakeMode(AbstractMotor::brakeMode::hold);
    leftTop.setBrakeMode(AbstractMotor::brakeMode::hold);
    leftBottom.setBrakeMode(AbstractMotor::brakeMode::hold);

    rightFront.setBrakeMode(AbstractMotor::brakeMode::hold);
    rightTop.setBrakeMode(AbstractMotor::brakeMode::hold);
    rightBottom.setBrakeMode(AbstractMotor::brakeMode::hold);
  }

  else if (controller.getDigital(ControllerDigital::right) == 1) {
    leftFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftTop.setBrakeMode(AbstractMotor::brakeMode::coast);
    leftBottom.setBrakeMode(AbstractMotor::brakeMode::coast);

    rightFront.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightTop.setBrakeMode(AbstractMotor::brakeMode::coast);
    rightBottom.setBrakeMode(AbstractMotor::brakeMode::coast);
  }
  
  if (controller.getDigital(ControllerDigital::up) == 1) {
    pros::lcd::set_text(1, std::to_string(drive->getState().x.convert(okapi::foot)));
    pros::lcd::set_text(2, std::to_string(drive->getState().y.convert(okapi::foot)));
    pros::lcd::set_text(3, std::to_string(imu.controllerGet()));
  }
  
/*
    autonDirect(1);

    // roll 1

    // driveForward(1.65, true);
    // rotate(-90);
    // driveForward(2, false);

    // autonDirect(1);
*/

  if (controller.getDigital(ControllerDigital::B) == 1) {
    // roller
    // pros::Motor conveyor (9); 
    // conveyor.set_encoder_units(pros::E_MOTOR_ENCODER_DEGREES);
    // conveyor.move_relative(720, 600);

    // roll 1 2


    // rollUntilColor(1);
    driveForward(1.65, true);
    rotate(90);
    driveForward(2);
    // rollUntilColor(1);

    // roll 3 4

    // get to middle
    driveForward(10, true);
    rotate(178);

    // // rolling 3rd
    driveForward(8);
    // rollUntilColor(1);

    driveForward(1.65, true);
    rotate(-90);

    // // rolling 4th
    driveForward(2);
    // rollUntilColor(1);


    // rotate(-65);

    // int cnt = 0;

    // int prevError = 0;
    // while (cnt < 1) {
    //     double kP = 0.03;
    //     double ki = 0.0;
    //     double kd = 0.1;

    //     int error = 450-flywheel.getActualVelocity();
    //     int integral = integral + error;
    //     int derivative = error - prevError;
    //     int prevError = error;
    //     int p = error * kP;
    //     int i = integral * ki;
    //     int d = derivative * kd;

    //     flywheel.moveVelocity(500+p+i+d);

    //     if (error - 25 <= 0 || error + 25 >= 0) {
    //         indexer.set_value(false);
    //         pros::delay(700);
    //         indexer.set_value(true);
    //         cnt++;
    //     }

    //     pros::delay(10);
    // }

    // cnt = 0;
    // pros::delay(2000);
    // rotate(180);
  } 
}


