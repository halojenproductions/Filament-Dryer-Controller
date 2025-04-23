#include "button.h"
#include <Arduino.h>

volatile byte interruption			= 0;
volatile uint32_t interruptTime		= 0;
static constexpr byte debounceDelay = 20;

bool interrupted() {
	return interruption & 1;
}

void interruptHandler() {
	interruption |= 1;
	interruptTime = millis();

	if (digitalRead(pButt) == LOW) {
		interruption |= (1 << 1);	  // Button down.
	} else {
		interruption &= ~(1 << 1);	  // Button up.
	}
}

void interruptAnalyser() {
	if (millis() >= interruptTime + debounceDelay) {
		// Clear the interrupt flag.
		interruption &= ~1;

		if (ops.getStatus(Ops::Status::ScreenAwake)) {
			// If the screen is awake, touch its timer.
			ops.screenTimeout.reset();
		} else {
			// Otherwise wake it up.
			ops.setCommand(Ops::Command::WakeUp);
		}

		// Process the button change.
		if (interruption & (1 << 1)) {
			// Button went down.
			ops.buttonHold.reset();
			ops.setStatus(Ops::Status::ButtonDown);
			// Allow hold only if the screen was awake.
			if (ops.getStatus(Ops::Status::ScreenAwake)) {
				ops.clearCommand(Ops::Command::ButtonHoldHandled);
			}
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

void buttonClicked() {
	// Check if we are in selection mode.
	if (ops.getStatus(Ops::Status::Select)) {
		filaments.next();
		ops.setDirty(Ops::Dirty::Filament);
		ops.selectionTimeout.reset();
	}

	// Nothing else to do because we already told it to wake up if it was asleep.
	// But we might as well do a full screen update at this point.
	ops.setDirty(Ops::Dirty::All);
}

void buttonHeld() {
	ops.setCommand(Ops::Command::ButtonHoldHandled);
	ops.screenTimeout.reset();

	// Check if we are in selection mode.
	if (ops.getStatus(Ops::Status::Select)) {
		filaments.apply();
		ops.clearStatus(Ops::Status::Select);
	} else {
		ops.setStatus(Ops::Status::Select);
		ops.selectionTimeout.reset();
	}

	ops.setDirty(Ops::Dirty::Filament);
}
