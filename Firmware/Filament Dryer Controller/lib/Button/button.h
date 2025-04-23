#ifndef BUTTON_H
#define BUTTON_H

#include "filaments.h"
#include "operations.h"
#include "pins.h"
#include <Arduino.h>

namespace Button {

	// Declare external dependencies
	extern Ops& ops;
	extern Filaments& filaments;

	// Interrupt stuff.
	extern bool interrupted();
	extern void interruptHandler();
	extern void interruptAnalyser();

	// Other buttony stuff.
	extern void buttonHeld();
	extern void buttonClicked();
}

#endif
