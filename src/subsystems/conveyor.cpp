#include "main.h"

using namespace okapi;

void updateConveyor() {
    if (controller.getDigital(ControllerDigital::R1) == 1) {
        conveyorIntake.moveVelocity(600);
    }
    else if (controller.getDigital(ControllerDigital::R2) == 1) {
        conveyorIntake.moveVelocity(-600);
    }
    else {
        conveyorIntake.moveVelocity(0);
    }
}