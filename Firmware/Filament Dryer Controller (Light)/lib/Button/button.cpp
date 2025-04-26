#include "button.h"

namespace Button {
#define BUTT_TRIG 0	   // Button interrupt triggered bit.
#define BUTT_DIR 1	   // Button direction bit (pressed or released). 1 = down.

	volatile byte interruption = 0;
	volatile uint32_t timeDown = 0;
	volatile uint32_t timeUp   = 0;

	bool interrupted() {
		return interruption & 1;
	}

	void interruptHandler() {
		interruption |= 1;

		if (digitalRead(Pins::pButt) == LOW) {
			if (millis() >= timeDown + debounceDelay) {
				timeDown = millis();
			}
			interruption |= (1 << 1);	  // Button down.
		} else {
			interruption &= ~(1 << 1);	  // Button up.
			timeUp = millis();
		}
	}

	void interruptAnalyser() {
		Serial.println(F("Button::interruptAnalyser()"));
		// Clear the interruption.
		bitClear(interruption, BUTT_TRIG);

		if (bitRead(interruption, BUTT_DIR) && !bitRead(Sys::statuses, Sys::STATUS_BUTTON_DOWN)) {
			/// Button is down for the first time.
			// Set button down status.
			bitSet(Sys::statuses, Sys::STATUS_BUTTON_DOWN);
			// Start hold timer.
			Util::resetTimer(Sys::buttonHoldTimeout);
			bitClear(Sys::commands, Sys::COMMAND_BUTTON_HOLD_HANDLED);
			// If screen is asleep, instruct it to wake up.
			if (!bitRead(Sys::statuses, Sys::STATUS_AWAKE)) {
				bitSet(Sys::commands, Sys::COMMAND_WAKEUP);
			}
		} else if (!bitRead(interruption, BUTT_DIR)) {
			/// Button is released and not bouncing.
			// Set button up status.
			bitClear(Sys::statuses, Sys::STATUS_BUTTON_DOWN);

			if (timeUp - timeDown >= debounceDelay) {
				// Determine whether it was clicked or held.
				if (!Util::getTimer(Sys::buttonHoldTimeout)) {
					// Button was clicked.
					buttonClicked();
				}
			} else {
				Serial.print(F("Skipped short click: "));
				Serial.println(timeUp - timeDown);
			}
		}
	}

	void buttonClicked() {
		Serial.println(F("Button::buttonClicked()"));
		// Check if we are in selection mode.
		if (bitRead(Sys::statuses, Sys::STATUS_SELECT)) {
			Filaments::next();
			bitSet(Sys::dirties, Sys::DIRTY_FILAMENT);
			Util::resetTimer(Sys::selectionTimeout);
		} else {
			Util::resetTimer(Sys::idleInputPolling);

			bitSet(Sys::statuses, Sys::STATUS_ACTIVE);
			bitSet(Sys::dirties, Sys::DIRTY_ALL);
		}
	}

	void buttonHeld() {
		Serial.println(F("Button::buttonHeld()"));
		bitSet(Sys::commands, Sys::COMMAND_BUTTON_HOLD_HANDLED);

		// Check if we are in selection mode.
		if (bitRead(Sys::statuses, Sys::STATUS_SELECT)) {
			Filaments::apply();
			bitClear(Sys::statuses, Sys::STATUS_SELECT);
		} else {
			Util::resetTimer(Sys::selectionTimeout);
			bitSet(Sys::statuses, Sys::STATUS_SELECT);
		}

		bitSet(Sys::dirties, Sys::DIRTY_FILAMENT);
	}
}
