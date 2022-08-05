#include "main.h"

using namespace okapi;

Motor flywheel(flywheelPort, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

bool toggled = false;

void updateFlywheel() {
    if (controller.getDigital(ControllerDigital::L1) == 1) {
        if (toggled) {
            flywheel.moveVelocity(0);
        }
        else
            flywheel.moveVelocity(500);
        toggled = !toggled;
    }
    
}