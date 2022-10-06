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
    .withSensors(
        ADIEncoder{encoderLPort1, encoderLPort2}, // Left encoder
        ADIEncoder{encoderRPort1, encoderRPort2},  // Right encoder
        ADIEncoder{encoderCPort1, encoderCPort2, true}  // Center encoder reversed
    )
    // Specify the tracking wheels diam (2.75 in), track (7 in), and TPR (360)
    .withOdometry({{2.75_in, 7.5_in, 1_in, 2.75_in}, quadEncoderTPR})
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
  if (controller.getDigital(ControllerDigital::X) == 1) {
    // auton 
    drive->setState({115_in, 8.75_in, 180_deg});

    drive->driveToPoint({115_in, 11_in}, true);
    pros::delay(100);

    drive->turnToPoint({23_in, 23_in});
    pros::delay(100);

    drive->driveToPoint({53_in, 18_in});
    pros::delay(100);

    // conveyor.moveVelocity(600);
    // pros::delay(100);
  }
  if (controller.getDigital(ControllerDigital::up) == 1) {
    pros::lcd::set_text(1, std::to_string(drive->getState().x.convert(okapi::inch)));
    pros::lcd::set_text(2, std::to_string(drive->getState().y.convert(okapi::inch)));
    pros::lcd::set_text(3, std::to_string(drive->getState().theta.convert(okapi::degree)));
  }
  if (controller.getDigital(ControllerDigital::X) == 1) {
    rotate(0);
    // driveForward(2);
  } 
}