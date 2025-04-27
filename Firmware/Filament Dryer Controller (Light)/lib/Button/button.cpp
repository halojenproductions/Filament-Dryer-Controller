#include "button.h"

namespace Button {
	using namespace Sys;
	using namespace Util;
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

		if (bitRead(interruption, BUTT_DIR) && !getStatus(Status::ButtonDown)) {
			/// Button is down for the first time.
			// Set button down status.
			setStatus(Status::ButtonDown);
			// Start hold timer.
			resetTimer(buttonHoldTimeout);
			setCommand(Command::HandleButtonHold);
			// If screen is asleep, instruct it to wake up.
			if (!getStatus(Status::ScreenAwake)) {
				setCommand(Command::WakeUp);
			}
		} else if (!bitRead(interruption, BUTT_DIR)) {
			/// Button is released and not bouncing.
			// Set button up status.
			clearStatus(Status::ButtonDown);

			if (timeUp - timeDown >= debounceDelay) {
				// Determine whether it was clicked or held.
				if (!getTimer(buttonHoldTimeout)) {
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
		if (getStatus(Status::Select)) {
			Filaments::next();
			UI::setDirty(UI::Dirty::Filament);
			resetTimer(selectionTimeout);
		} else {
			resetTimer(idleInputPolling);

			setStatus(Status::Active);
			UI::setDirty(UI::Dirty::All);
		}
	}

	void buttonHeld() {
		Serial.println(F("Button::buttonHeld()"));
		clearCommand(Command::HandleButtonHold);

		// Check if we are in selection mode.
		if (getStatus(Status::Select)) {
			Filaments::apply();
			clearStatus(Status::Select);
		} else {
			resetTimer(selectionTimeout);
			setStatus(Status::Select);
		}

		UI::setDirty(UI::Dirty::Filament);
	}
}
