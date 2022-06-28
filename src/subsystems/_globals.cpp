#include "main.h"

okapi::Controller controller;
okapi::Rate rate;

okapi::ADIEncoder leftEncoder = ADIEncoder({1, 'A', 'B'}, false);
okapi::ADIEncoder rightEncoder = ADIEncoder({1, 'A', 'B'}, false);
okapi::ADIEncoder backEncoder = ADIEncoder({1, 'A', 'B'}, false);
