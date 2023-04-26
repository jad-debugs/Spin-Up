#include "main.h"
// #include "subsystems/selection.hpp"
#include "pros/rtos.hpp"
#include "subsystems/auton.hpp"
#include "subsystems/drive.hpp"
#include "subsystems/expansion.hpp"
#include "subsystems/flywheel.hpp"
#include "subsystems/indexer.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/odom.hpp"
#include "subsystems/blooper.hpp"

// using namespace okapi;

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {

  intakeInit();
  fwInit();
  expansionInit();
  blooperInit();
  indexerInit();
  imuInnit();
  IEInnit();
  // selector::init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will rpestart the task, not re-start
 * it from where it left off.
 */
void autonomous() {

  // autonDirect();
  // autonIndirect();
  skills(1);
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 \

 */
void opcontrol() {
  while (true) {
    updateDrive();
    updateConveyor();
    updateIndexer();
    updateExpansion();
    updateBlooper();

    pros::Controller master (pros::E_CONTROLLER_MASTER);
   
    int count = 0;
    std::string power = "";
    if (!(count % 3000)) {
      if (flywheel.getActualVelocity() < 100){
        power = "OFF    ";
      } else {
        power = "ON     ";
      }
      if (flywheel.getActualVelocity() < 150){
        master.print(0, 0, "flySpeed: %i %s", 0 , power);
      } else {
      // Only print every 50ms, the controller text update rate is slow
      master.print(0, 0, "flySpeed: %i %s", (int)(flywheel.getActualVelocity()), power);
      }
      
    }
    count++;
    pros::delay(2);
  

    // updateOdom();
    pros::delay(10);

  }
}
