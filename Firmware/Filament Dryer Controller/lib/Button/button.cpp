#include "button.h"
#include <Arduino.h>

volatile byte interrupt			= 0;
volatile uint32_t interruptTime = 0;

static const int debounceDelay = 50;	// Debounce delay in milliseconds

void handleButtonInterrupt() {
	interrupt |= 1;
	interruptTime = millis();

	if (digitalRead(pButt) == LOW) {
		interrupt |= (1 << 1);	   // Button down.
	} else {
		interrupt &= ~(1 << 1);	   // Button up.
	}
}

void buttonInterruption() {
	if (interrupt & 1) {
		// Button changed state.
		if (millis() >= interruptTime + debounceDelay) {
			// Clear the interrupt flag.
			interrupt &= ~1;

			// Ensure the screen is awake, regardless of which way it changed.
			ops.screenTimeout.reset();
			if (!ops.getStatus(Ops::Status::ScreenAwake)) {
				ops.setCommand(Ops::Command::WakeUp);
			}

			// Process the button change.
			if (interrupt & (1 << 1)) {
				// Button went down.
				ops.buttonHold.reset();
				ops.setStatus(Ops::Status::ButtonDown);
				ops.clearCommand(Ops::Command::ButtonHoldHandled);
			} else {
				// Button was released.
				ops.clearStatus(Ops::Status::ButtonDown);
				// If we haven't surpassed the hold timer it must be a click.
				if (!ops.buttonHold.get(currentTime)) {
					ops.setCommand(Ops::Command::ButtonClick);
				}
			}
		}
	}
}

void buttonHeld() {
	// Button was held.
	ops.setCommand(Ops::Command::ButtonHoldHandled);
	ops.screenTimeout.reset();

	ops.setDirty(Ops::Dirty::Top);
	ops.setDirty(Ops::Dirty::Bottom);

	// Check if we are in selection mode.
	if (ops.getStatus(Ops::Status::Select)) {
		// TODO: Accept and Update filament settings.
		ops.clearStatus(Ops::Status::Select);
	} else {
		ops.setStatus(Ops::Status::Select);
	}
}
