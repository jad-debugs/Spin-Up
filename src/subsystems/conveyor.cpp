#include "main.h"

using namespace okapi;

Motor conveyor(conveyorPort, false, AbstractMotor::gearset::blue,
               AbstractMotor::encoderUnits::degrees);

enum class IntakeState {
  STOPPED = 0,
  INTAKING = 1,
  OUTTAKING = 2,
};

IntakeState currentIntakeState = IntakeState::STOPPED;
IntakeState previousIntakeState = IntakeState::STOPPED;

ControllerButton intakeButton = ControllerButton(ControllerDigital::L1);
ControllerButton outakeButton = ControllerButton(ControllerDigital::down);

void intakeInit() { conveyor.setBrakeMode(AbstractMotor::brakeMode::coast); }

void updateConveyor() {

  if (outakeButton.changedToPressed()) {
    previousIntakeState = currentIntakeState;
    currentIntakeState = IntakeState::OUTTAKING;
  } else if (outakeButton.changedToReleased()) {
    currentIntakeState = previousIntakeState;
  }

  if (intakeButton.changedToPressed()) {
    if (currentIntakeState == IntakeState::INTAKING) {
      previousIntakeState = currentIntakeState;
      currentIntakeState = IntakeState::STOPPED;
    } else {
      previousIntakeState = currentIntakeState;
      currentIntakeState = IntakeState::INTAKING;
    }
  }

  switch (currentIntakeState) {
  case IntakeState::STOPPED:
    conveyor.moveVoltage(0);
    break;
  case IntakeState::INTAKING:
    conveyor.moveVoltage(12000);
    break;
  case IntakeState::OUTTAKING:
    conveyor.moveVoltage(-12000);
    break;
  }
}