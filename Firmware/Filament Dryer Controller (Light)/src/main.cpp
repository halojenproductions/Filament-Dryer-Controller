// #include <Adafruit_GFX.h>
#include <Arduino.h>
// #include <u8g2lib.h>

#include "button.h"
#include "control.h"
#include "filaments.h"
#include "htsensor.h"
#include "pins.h"
#include "system.h"
#include "ui.h"
#include "utilities.h"

#define DEBUG_MODE 0

void setup() {
	// Setup serial write output.
	delay(1000);

	Serial.begin(9600);
	while (!Serial) {	 // Wait for serial port to connect
		delay(10);
	}
	Serial.println(F(""));
	Serial.println(F("> Setup start"));

	// Set up pins.
	// Serial.println(F("Pins"));
	Serial.println(F("Pins::setupPins()"));
	Pins::setupPins();

	// Load saved filament.
	Serial.println(F("Filaments::retrieve()"));
	Filaments::retrieve();

	// Set up oled display.
	// Serial.println("UI");
	Serial.println(F("UI::setupScreen()"));
	UI::setupScreen();

	// ops.currentTime = millis();

	// TODO move to a setup method in HtSensor.
	// Set up humidity & temperature sensor.
	Serial.println(F("HtSensor::setupSensor()"));
	HtSensor::setupSensor();

	// Set up button interrupt.
	Serial.println(F("Attaching interrupt"));
	attachInterrupt(digitalPinToInterrupt(Pins::pButt), Button::interruptHandler, CHANGE);

	// Set initial values.
	Serial.println(F("Setting initial values"));
	bitSet(Sys::commands, Sys::COMMAND_BUTTON_HOLD_HANDLED);
	bitSet(Sys::commands, Sys::COMMAND_WAKEUP);
	bitSet(Sys::statuses, Sys::STATUS_OK);
	digitalWrite(Pins::pLedOk, bitRead(Sys::statuses, Sys::STATUS_OK));
	bitSet(Sys::statuses, Sys::STATUS_ACTIVE);
	// Control::idle();

	// Serial.println(F("Setup finished"));
}

void loop() {
	// Serial.println(F(""));
	// Serial.println(F("> Main loop start"));

	Sys::currentTime = millis();

	// Wrangle interruption.
	if (Button::interrupted()) {
		// Button changed state. Go and deal with that.
		Button::interruptAnalyser();
	}

	// Wake up.
	if (Util::bitCheck(Sys::commands, Sys::COMMAND_WAKEUP)) {
		UI::wakeUp();
	}

	if (bitRead(Sys::statuses, Sys::STATUS_BUTTON_DOWN)) {
		// Touch timers.
		Util::resetTimer(Sys::screenTimeout);
		Util::resetTimer(Sys::selectionTimeout);
	}

	// Button held.
	if (bitRead(Sys::statuses, Sys::STATUS_BUTTON_DOWN)
		&& Util::getTimer(Sys::buttonHoldTimeout)
		&& !bitRead(Sys::commands, Sys::COMMAND_BUTTON_HOLD_HANDLED)) {
		Button::buttonHeld();
	}

	// Read sensors.

	if ((bitRead(Sys::statuses, Sys::STATUS_ACTIVE) && Util::checkTimer(Sys::activeInputPolling))
		|| (!bitRead(Sys::statuses, Sys::STATUS_ACTIVE) && Util::checkTimer(Sys::idleInputPolling)
		)) {
		// Serial.println(F("Read sensors"));

		/// Check thermistor.
		// TODO Remove mocky shit.
		Util::checkTherm(50);
		// TODO uncomment: ops.checkTherm(Thermistor::adcToCelsius(analogRead(Pins::pTemp)));

		/// Check humidity.
		// TODO Remove mocky shit.
		float humidity = 50 + (int)random(2);
		if (Util::checkHumidity(humidity)) {
			// TODO uncomment: if(ops.checkHumidity(HtSensor::sensor.readHumidity())) {
			bitSet(Sys::dirties, Sys::DIRTY_HUMIDITY);
		}

		/// Check temperature.
		// TODO Remove mocky shit.
		float inTemperature = 20 + (int)random(2);
		if (Util::checkTemperature(inTemperature)) {
			// TODO uncomment: if(ops.checkTemperature(HtSensor::sensor.readTemperature())) {
			bitSet(Sys::dirties, Sys::DIRTY_TEMP);
		}
	}

	// Control loop.

	if (bitRead(Sys::statuses, Sys::STATUS_ACTIVE)) {
		Control::active();
	} else {
		Control::idle();
	}

	// Set statuses. or should that be commands?
	if (bitRead(Sys::statuses, Sys::STATUS_ERROR)) {
		// Serial.println(F("Status::Error"));

		bitClear(Sys::statuses, Sys::STATUS_OK);
		digitalWrite(Pins::pLedOk, bitRead(Sys::statuses, Sys::STATUS_OK) ? HIGH : LOW);
	}

	if (bitRead(Sys::statuses, Sys::STATUS_HEATING)) {
	}

	// Update display.
	if (bitRead(Sys::statuses, Sys::STATUS_AWAKE)) {
		/* Only for full frame buffer.
		// Load the display buffer.
		UI::drawUI();

		// Send the display buffer (or just bits of it).
		UI::updateScreen_FullFrameBuffer();
		*/

		UI::updateScreen();

		// Selection timeout.
		if (bitRead(Sys::statuses, Sys::STATUS_SELECT) && Util::checkTimer(Sys::selectionTimeout)) {
			Serial.println(F("Selection timeout"));
			bitClear(Sys::statuses, Sys::STATUS_SELECT);
			Filaments::cancel();
			bitSet(Sys::dirties, Sys::DIRTY_FILAMENT);
		}

		// Screen timeout.
		if (!bitRead(Sys::statuses, Sys::STATUS_BUTTON_DOWN)
			&& Util::checkTimer(Sys::screenTimeout)) {
			Serial.println(F("Screen timeout."));
			UI::sleep();
		}
	}
	// delay(10000);
}
