#ifndef CONTROLLOOP_H
#define CONTROLLOOP_H

#include "operations.h"
#include "pins.h"
#include <Arduino.h>

namespace ControlLoop {
	extern Ops& ops;
	extern Filaments& filaments;

	extern void active();
	extern void idle();

	// TODO? maybe turn the namespace into a singleton class and make these private?
	extern void heaterDuty();
	extern void heaterOn();
	extern void heaterOff();
	extern void fanOnLow();
	extern void fanOnHigh();
	extern void fanOff();
}

#endif
