#include "flywheel.hpp"
#include "main.h"
#include "okapi/impl/device/button/controllerButton.hpp"
#include "okapi/impl/device/controllerUtil.hpp"
#include "ports.hpp"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/rtos.hpp"

using namespace okapi;

Motor flywheel(flywheelPort, false, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);

static float target = 0;
static const float rpmWindow = 30.0f;

ControllerButton midFlywheelToggle = ControllerButton(ControllerDigital::R1);
ControllerButton lowFlywheelToggle = ControllerButton(ControllerDigital::R2);
ControllerButton highFlywheelToggle = ControllerButton(ControllerDigital::X);
ControllerButton reverseToggle = ControllerButton(ControllerDigital::left);

void fwInit() {
  flywheel.setBrakeMode(AbstractMotor::brakeMode::coast);
  pros::Task flywheelControlHandle((controlFlywheelTask));
  pros::Task updateFlywheelHandle((updateFlywheelTask));
}

// void controlFlywheelTask(void *) {
//   while (true) {
//     if (target == 0) {
//       flywheel.moveVelocity(0);
//       continue;
//     }
//     float error = target - (flywheel.getActualVelocity() * 5.0f);
//     if (error > (target - rpmWindow)) {
//       flywheel.moveVoltage(target -
//                            (flywheel.getActualVelocity() * 5.0f * error /
//                            100));

//     } else if (error <= -rpmWindow) {
//       flywheel.moveVoltage(pros::c::motor_get_voltage(7) - 100);
//     } else { // Within threshold window -> Use Feedforward and P Controller
//       flywheel.moveVoltage((target * 4.8f) + (error * 1.4f));
//     }
//     pros::delay(20);
//   }
// }



void controlFlywheelTask(void *) {
  bool max = false;
   //static std::string power;
     
  // while (true) {   
  //   if (currentFlywheelState != FlywheelState::OFF) {
  //     if (flywheel.getActualVelocity() < (target - 280)) {
  //       // flywheel.controllerSet(1);
  //       flywheel.moveVelocity(600);
  //       // power = "ON";
  //       } else {
  //       // flywheel.controllerSet(0.75);
  //       flywheel.moveVelocity(target);
  //       // power = "ON";
  //     }
      
  //     } else {
  //     // flywheel.controllerSet(0);
  //     flywheel.moveVelocity(0);
  //     // power = "OFF";
  //   }
  // }
     
  while (true) {   
    if (currentFlywheelState != FlywheelState::OFF) {
      if (currentFlywheelState != FlywheelState::MID_SPEED) {
        if (flywheel.getActualVelocity() < (target - 280)) {
          // flywheel.controllerSet(1);
          flywheel.moveVelocity(600);
          // power = "ON";
        } else {
          // flywheel.controllerSet(0.75);
          flywheel.moveVelocity(target);
          // power = "ON";
        }
      } else {
         if (flywheel.getActualVelocity() < (target - 60)) {
          // flywheel.controllerSet(1);
          flywheel.moveVelocity(600);
          // power = "ON";
        } else {
          // flywheel.controllerSet(0.75);
          max = true;
          flywheel.moveVelocity(target);
          // power = "ON";
        }
      }

    } else {
      // flywheel.controllerSet(0);
      flywheel.moveVelocity(0);
      // power = "OFF";
    }
  }
}

void updateFlywheelTask(void *) {
  while (true) {
    if (lowFlywheelToggle.changedToPressed()) {
      if (currentFlywheelState != FlywheelState::LOW_SPEED) {
        currentFlywheelState = FlywheelState::LOW_SPEED;
      } else {
        currentFlywheelState = FlywheelState::OFF;
      }
    }
    
    if (midFlywheelToggle.changedToPressed()) {
      if (currentFlywheelState != FlywheelState::MID_SPEED) {
        currentFlywheelState = FlywheelState::MID_SPEED;
      } else {
        currentFlywheelState = FlywheelState::OFF;
      }
    }

    if (highFlywheelToggle.changedToPressed()) {
      if (currentFlywheelState != FlywheelState::HIGH_SPEED) {
        currentFlywheelState = FlywheelState::HIGH_SPEED;
      } else {
        currentFlywheelState = FlywheelState::OFF;
      }
    }

    if (reverseToggle.changedToPressed()) {
      if (currentFlywheelState != FlywheelState::REVERSE) {
        currentFlywheelState = FlywheelState::REVERSE;
      } else {
        currentFlywheelState = FlywheelState::OFF;
      }
    }

    switch (currentFlywheelState) {
    case FlywheelState::OFF:
      target = 0;
      break;
    case FlywheelState::LOW_SPEED:
      target = 385;
      break;
    case FlywheelState::MID_SPEED:
      target = 405;
      break;
    case FlywheelState::HIGH_SPEED:
      target = 500;
      break;
    case FlywheelState::REVERSE:
      target = -150;
      break;
    case FlywheelState::AUTONFULLCOURT:
      target = 1950;
      break;
    case FlywheelState::AUTONLOW:
      target = 400;
      break;
    }
    pros::delay(20);
  }
}

FlywheelState getFWState() { return currentFlywheelState; }

void setFWState(FlywheelState FWstate) { currentFlywheelState = FWstate; }
