#pragma once
#include "main.h"

using namespace okapi;

extern pros::ADIDigitalOut blooper;
extern pros::ADIDigitalIn blooperButton;

void blooperInit();
void updateBlooper();