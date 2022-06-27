#include "main.h"

using namespace okapi;

Motor conveyor(conveyorPort, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

void updateConveyor() {
    if (controller.getDigital(ControllerDigital::R1) == 1) {
        conveyor.moveVelocity(100);
    }
    else if (controller.getDigital(ControllerDigital::R2) == 1) {
        conveyor.moveVelocity(-100);
    }
    else {
        conveyor.moveVelocity(0);
    }
}