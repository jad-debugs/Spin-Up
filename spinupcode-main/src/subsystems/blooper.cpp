#include "main.h"
#include "okapi/impl/device/button/controllerButton.hpp"
#include "okapi/impl/device/controllerUtil.hpp"
#include "ports.hpp"
#include "pros/adi.hpp"
#include "pros/rtos.hpp"

using namespace okapi;

pros::ADIDigitalOut blooper = pros::ADIDigitalOut(blooperPort);

ControllerButton blooperButton = ControllerButton(ControllerDigital::down);



void blooperInit() { blooper.set_value(false); }
int stateB = 0;



void updateBlooper() {
  if (blooperButton.changedToPressed()) {
    if(stateB == 0){
     blooper.set_value(true);
     stateB++;
    } else{
     blooper.set_value(false);
     stateB--;
    }
  }
}