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
  
  if (controller.getDigital(ControllerDigital::up) == 1) {
    pros::lcd::set_text(1, std::to_string(drive->getState().x.convert(okapi::foot)));
    pros::lcd::set_text(2, std::to_string(drive->getState().y.convert(okapi::foot)));
    pros::lcd::set_text(3, std::to_string(imu.controllerGet()));
  }
  
  if (controller.getDigital(ControllerDigital::B) == 1) {
    rotate(90);
    driveForward(3);
    rotate(115);

    int cnt = 0;

    // while (cnt < 2) {
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

    //     rate.delay(10);
    // }

    cnt = 0;
    // pros::delay(2000);
    rotate(180);
  } 
}

class SelectionSort {
  void sort(int arr[]) {
    int n = arr.length;
    for (int i = 0; i < n; i++) {
      int min_idx = i;
      for (int j = i+1; j < n; j++) {
        if (arr[j] < arr[min_idx])
          j = min_idx;
      }
      int temp = arr[min_idx];
      arr[min_idx] = arr[i];
      arr[i] = temp;
    }
  }
}