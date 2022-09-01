#include "main.h"

using namespace okapi;

bool released1 = true;
bool released2 = true;
bool toggle1 = false;
bool toggle2 = false;

Motor conveyor(conveyorPort, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

void updateConveyor()
{
  if (released3 && released4) {
    if (controller.getDigital(ControllerDigital::R1) == 0)
    {
      released1 = true;
    }

    if (controller.getDigital(ControllerDigital::R1) == 1 && released1)
    {
      released1 = false;

      toggle2 = false;
      released2 = true;
      if (!toggle1){
        conveyor.moveVelocity(600);
        toggle1 = true;
      } else if (toggle1){
        conveyor.moveVelocity(0);
        toggle1 = false;
      }

    }

    if (controller.getDigital(ControllerDigital::R2) == 0)
    {
        released2 = true;
    }

if (controller.getDigital(ControllerDigital::R2) == 1 && released2){
      released2 = false;

      toggle1 = false;
      released3 = true;
      if (!toggle2){
        conveyor.moveVelocity(-600);
        toggle2 = true;
} else if (toggle2){
        conveyor.moveVelocity(0);
        toggle2 = false;
      }

    }
  }
  else {
    conveyor.moveVelocity(0);
  }

}
