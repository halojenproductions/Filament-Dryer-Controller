#include "button.h"

namespace Button {

	volatile byte interruption			= 0;
	volatile uint32_t interruptTime		= 0;
	static constexpr byte debounceDelay = 20;

	bool interrupted() {
		return interruption & 1;
	}

	void interruptHandler() {
		interruption |= 1;
		interruptTime = millis();

		if (digitalRead(Pins::pButt) == LOW) {
			interruption |= (1 << 1);	  // Button down.
		} else {
			interruption &= ~(1 << 1);	  // Button up.
		}
	}

	void interruptAnalyser() {
		if (millis() >= interruptTime + debounceDelay) {
			// Clear the interrupt flag.
			interruption &= ~1;

			if (bitRead(Sys::statuses, Sys::STATUS_AWAKE)) {
				// If the screen is awake, touch its timer.
				// ops.screenTimeout.reset();
				Util::resetTimer(Sys::TIMER_SCREEN_TIMEOUT);
			} else {
				// Otherwise wake it up.
				bitSet(Sys::commands, Sys::COMMAND_WAKEUP);
			}

			// Process the button change.
			if (interruption & (1 << 1)) {
				// Button went down.
				// ops.buttonHold.reset();
				Util::resetTimer(Sys::TIMER_BUTTON_HOLD);
				bitSet(Sys::statuses, Sys::STATUS_BUTTON_DOWN);
				// Allow hold only if the screen was awake.
				if (bitRead(Sys::statuses, Sys::STATUS_AWAKE)) {
					bitSet(Sys::commands, Sys::COMMAND_BUTTON_HOLD_HANDLED);
				}
			} else {
				// Button was released.
				bitClear(Sys::statuses, Sys::STATUS_BUTTON_DOWN);

				// If we haven't surpassed the hold timer it must be a click.
				// if (!ops.buttonHold.get(ops.currentTime)) {
				if (!Util::getTimer(Sys::TIMER_BUTTON_HOLD)) {
					// Do click command only if the screen was awake.
					if (bitRead(Sys::statuses, Sys::STATUS_AWAKE)) {
						Serial.println(F("Interrupt analyser setting button clicked."));
						bitSet(Sys::commands, Sys::COMMAND_BUTTON_CLICKED);
					}
					// If it was asleep, we've already told it to wake up so we are done here.
				}
			}
		}
	}

	void buttonClicked() {
		// Check if we are in selection mode.
		if (bitRead(Sys::statuses, Sys::STATUS_SELECT)) {
			// ops.selectionTimeout.reset();
			Util::resetTimer(Sys::TIMER_SELECTION_TIMEOUT);
			Filaments::next();
			bitSet(Sys::dirties, Sys::DIRTY_FILAMENT);
		} else {
			bitSet(Sys::statuses, Sys::STATUS_ACTIVE);
			bitSet(Sys::dirties, Sys::DIRTY_ALL);
		}
	}

	void buttonHeld() {
		bitSet(Sys::commands, Sys::COMMAND_BUTTON_HOLD_HANDLED);
		// ops.screenTimeout.reset();
		Util::resetTimer(Sys::TIMER_SCREEN_TIMEOUT);

		// Check if we are in selection mode.
		if (bitRead(Sys::statuses, Sys::STATUS_SELECT)) {
			Filaments::apply();
			bitClear(Sys::statuses, Sys::STATUS_SELECT);
		} else {
			bitSet(Sys::statuses, Sys::STATUS_SELECT);
			// ops.selectionTimeout.reset();
			Util::resetTimer(Sys::TIMER_SELECTION_TIMEOUT);
		}

		bitSet(Sys::dirties, Sys::DIRTY_FILAMENT);
	}
}
