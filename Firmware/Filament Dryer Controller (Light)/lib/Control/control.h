#ifndef CONTROLLOOP_H
#define CONTROLLOOP_H

#include "filaments.h"
#include "pins.h"
#include "system.h"
#include "timer.h"
#include "utilities.h"
#include <Arduino.h>

namespace Control {
	extern Timer activeTimeout;
	extern Timer activeCooldown;
	extern Timer heatingTimeout;
	extern Timer heatDutyTimeout;
	extern Timer heatingCooldown;

	extern void active();
	extern void idle();

	// TODO? maybe turn the namespace into a singleton class and make these private?
	extern void heaterDuty();
	extern void heaterOn();
	extern void heaterOff();
	extern void fanLow();
	extern void fanHigh();
	extern void fanOff();
}

#endif
