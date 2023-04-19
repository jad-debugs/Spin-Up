#pragma once
#include "main.h"

using namespace okapi;

extern Motor flywheel;

extern void fwInit();

enum class FlywheelState {
  OFF = 0,
  LOW_SPEED = 1,
  MID_SPEED = 2,
  HIGH_SPEED = 3,
  REVERSE = 4,
  AUTONFULLCOURT = 5,
  AUTONLOW = 6,
};

extern void updateFlywheelTask(void *);
extern void controlFlywheelTask(void *);
extern void flywheelBangBangControl(void*);

void print1(int error);
// static std::string power;
extern FlywheelState getFWState();
extern void setFWState(FlywheelState FWstate);

static FlywheelState currentFlywheelState = FlywheelState::OFF;
