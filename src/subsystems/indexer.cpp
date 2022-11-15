#include "main.h"

using namespace okapi;

pros::ADIDigitalOut indexer(indexerPort);

void updateIndexer() {
   if (controller.getDigital(ControllerDigital::X) == 1) {
       indexer.set_value(false);
       pros::delay(700);
       indexer.set_value(true);
   }
}