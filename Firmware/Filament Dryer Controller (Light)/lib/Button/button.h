#ifndef BUTTON_H
#define BUTTON_H

#include "filaments.h"
#include "pins.h"
#include "system.h"
#include "ui.h"
#include "utilities.h"
#include <Arduino.h>
#include <math.h>

namespace Button {
	// Interrupt stuff.
	extern volatile byte interruption;
	extern volatile uint32_t timeDown;
	extern volatile uint32_t timeUp;
	static constexpr byte debounceDelay = 10;

	extern bool interrupted();
	extern void interruptHandler();
	extern void interruptAnalyser();

	// Other buttony stuff.
	extern void buttonHeld();
	extern void buttonClicked();
}

#endif
