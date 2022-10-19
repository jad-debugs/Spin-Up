#include "main.h"

using namespace okapi;

Motor flywheel(flywheelPort, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::degrees);

bool released3 = true;
bool released4 = true;
bool toggle3 = false;
bool toggle4 = false;

int flywheelState;
bool released = true;
bool toggle = false;

int prevError = 0;

void updateFlywheel()
{
  if (released1 && released2) {
    if (controller.getDigital(ControllerDigital::L1) == 0)
    {
      released3 = true;
    }


    if (controller.getDigital(ControllerDigital::L1) == 1 && released3)
    {
      released3 = false;

      toggle4 = false;
      released4 = true;

      if (!toggle3){
        flywheel.moveVelocity(600);
        toggle3 = true;
      } else if (toggle3){
        flywheel.moveVelocity(0);
        toggle3 = false;

        // start intake when flywheel stops
        toggle1 = true;
        released1 = true;
      }
    
    }

    if (controller.getDigital(ControllerDigital::L2) == 0)
    {
      released4 = true;
    }

    if (controller.getDigital(ControllerDigital::L2) == 1 && released4){
      released4 = false;

      toggle3 = false;
      released3 = true;
    
      if (!toggle4){
        flywheel.moveVelocity(400);
        toggle4 = true;
      } else if (toggle4){
        flywheel.moveVelocity(0);
        toggle4 = false;

        // start intake when flywheel stops
        toggle1 = true;
        released1 = true;
      }
    }
  
    if (toggle4) {
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
    
    }
    else if (toggle3) {
      double kP = 0.03;
      double ki = 0.0;
      double kd = 0.1;

      int error = 375-flywheel.getActualVelocity();
      int integral = integral + error;
      int derivative = error - prevError;
      int prevError = error;
      int p = error * kP;
      int i = integral * ki;
      int d = derivative * kd;
    
      flywheel.moveVelocity(425+p+i+d);
    
    }
  }
  else {
    flywheel.moveVelocity(0);
  }
}
  

