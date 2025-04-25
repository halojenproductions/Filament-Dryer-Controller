#ifndef BUTTON_H
#define BUTTON_H

#include "filaments.h"
#include "pins.h"
#include "system.h"
#include "utilities.h"
#include <Arduino.h>

namespace Button {

	// Interrupt stuff.
	extern bool interrupted();
	extern void interruptHandler();
	extern void interruptAnalyser();

	// Other buttony stuff.
	extern void buttonHeld();
	extern void buttonClicked();
}

#endif
