#include "main.h"

using namespace okapi;

pros::ADIDigitalOut indexer(indexerPort);

void updateIndexer() {
   if (controller.getDigital(ControllerDigital::L2) == 1) {
       indexer.set_value(false);
       pros::delay(1000);
       indexer.set_value(true);
   }
}