#ifndef CONTROLLOOP_H
#define CONTROLLOOP_H

#include "operations.h"
#include "pins.h"
#include <Arduino.h>

namespace ControlLoop {
	extern Ops& ops;
	extern Filaments& filaments;

	extern void controlLoop();
	extern void active();
	extern void idle();
	extern void heaterOff();
	extern void fanOff();

}

#endif
