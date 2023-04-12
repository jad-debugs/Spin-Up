#include "main.h"

using namespace okapi;

pros::ADIDigitalOut indexer = pros::ADIDigitalOut(indexerPort);

ControllerButton indexerButton = ControllerButton(ControllerDigital::L2);

//void indexerInit() { indexer.set_value(false); }



void updateIndexer() {
  if (indexerButton.changedToPressed()) {
    indexer.set_value(true);
    pros::delay(500);
    indexer.set_value(false);
  }
}