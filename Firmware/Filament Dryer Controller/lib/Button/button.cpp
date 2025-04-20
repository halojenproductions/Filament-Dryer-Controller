#include "button.h"
#include <Arduino.h>

volatile byte interrupt			= 0;
volatile uint32_t interruptTime = 0;

static const int debounceDelay = 50;	// Debounce delay in milliseconds

bool interrupted() {
	return interrupt & 1;
}

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
	if (millis() >= interruptTime + debounceDelay) {
		// Clear the interrupt flag.
		interrupt &= ~1;

		if (ops.getStatus(Ops::Status::ScreenAwake)) {
			// If the screen is awake, touch its timer.
			ops.screenTimeout.reset();
		} else {
			// Otherwise wake it up.
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
				// Do click command only if the screen was awake.
				if (ops.getStatus(Ops::Status::ScreenAwake)) {
					ops.setCommand(Ops::Command::ButtonClick);
				}
				// If it was asleep, we've already told it to wake up so we are done here.
			}
		}
	}
}

void buttonHeld() {
	ops.setCommand(Ops::Command::ButtonHoldHandled);
	ops.screenTimeout.reset();

	// Check if we are in selection mode.
	if (ops.getStatus(Ops::Status::Select)) {
		filaments.apply();
		// TODO: Save the selection to EEPROM.
		ops.clearStatus(Ops::Status::Select);
	} else {
		ops.setStatus(Ops::Status::Select);
		ops.selectionTimeout.reset();
	}

	ops.setDirty(Ops::Dirty::Top);
	ops.setDirty(Ops::Dirty::Bottom);
}

void buttonClicked() {
	ops.clearCommand(Ops::Command::ButtonClick);
	ops.screenTimeout.reset();

	// Check if we are in selection mode.
	if (ops.getStatus(Ops::Status::Select)) {
		filaments.next();
		ops.setDirty(Ops::Dirty::Top);
		ops.setDirty(Ops::Dirty::Bottom);
		ops.selectionTimeout.reset();

		// digitalWrite(13, filaments.display.name == "PLA" ? HIGH : LOW);
		// delay(100);
		// digitalWrite(13, LOW);
	}
	// Nothing else to do because we already told it to wake up if it was asleep.
	ops.setDirty(Ops::Dirty::All);
}
