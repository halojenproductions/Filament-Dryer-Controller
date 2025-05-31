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
	Util::clearCommand(Sys::Command::HandleButtonHold);
	Util::setCommand(Sys::Command::WakeUp);
	Util::setStatus(Sys::Status::Ok);
	digitalWrite(Pins::pLedOk, Util::getStatus(Sys::Status::Ok));
	Util::setStatus(Sys::Status::Active);
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
	if (Util::checkCommand(Sys::Command::WakeUp)) {
		UI::wakeUp();
	}

	if (Util::getStatus(Sys::Status::ButtonDown)) {
		// Touch timers.
		Util::resetTimer(Sys::screenTimeout);
		Util::resetTimer(Sys::selectionTimeout);
	}

	// Button held.
	if (Util::getStatus(Sys::Status::ButtonDown)
		&& Util::getTimer(Sys::buttonHoldTimeout)
		&& Util::getCommand(Sys::Command::HandleButtonHold)) {
		Button::buttonHeld();
	}

	// Read sensors.

	if ((Util::getStatus(Sys::Status::Active) && Util::checkTimer(Sys::activeInputPolling))
		|| (!Util::getStatus(Sys::Status::Active) && Util::checkTimer(Sys::idleInputPolling))) {
		// Serial.println(F("Read sensors"));

		/// Check thermistor.
		// TODO Remove mocky shit.
		Util::checkTherm(50);
		// TODO uncomment: ops.checkTherm(Thermistor::adcToCelsius(analogRead(Pins::pTemp)));

		/// Check humidity.
		// TODO Remove mocky shit.
		// float humidity = 50 + (int)random(2);
		// if (Util::checkHumidity(humidity)) {
		if (Util::checkHumidity(HtSensor::sensor.readHumidity())) {
			UI::setDirty(UI::Dirty::Humidity);
		}

		/// Check temperature.
		// TODO Remove mocky shit.
		// float inTemperature = 20 + (int)random(2);
		// if (Util::checkTemperature(inTemperature)) {
		if (Util::checkTemperature(HtSensor::sensor.readTemperature())) {
			UI::setDirty(UI::Dirty::Temp);
		}
	}

	// Control loop.
	if (Util::getStatus(Sys::Status::Active)) {
		Control::active();
	} else {
		Control::idle();
	}

	// Set statuses. or should that be commands?
	if (Util::hasError()) {
		// Serial.println(F("Status::Error"));

		Util::clearStatus(Sys::Status::Ok);
		digitalWrite(Pins::pLedOk, Util::getStatus(Sys::Status::Ok) ? HIGH : LOW);
	}

	if (Util::getStatus(Sys::Status::Heating)) {
	}

	// Update display.
	if (Util::getStatus(Sys::Status::ScreenAwake)) {
		/* Only for full frame buffer.
		// Load the display buffer.
		UI::drawUI();

		// Send the display buffer (or just bits of it).
		UI::updateScreen_FullFrameBuffer();
		*/

		UI::updateScreen();

		// Selection timeout.
		if (Util::getStatus(Sys::Status::Select) && Util::checkTimer(Sys::selectionTimeout)) {
			Serial.println(F("Selection timeout"));
			Util::clearStatus(Sys::Status::Select);
			Filaments::cancel();
			UI::setDirty(UI::Dirty::Filament);
		}

		// Screen timeout.
		if (!Util::getStatus(Sys::Status::ButtonDown) && Util::checkTimer(Sys::screenTimeout)) {
			Serial.println(F("Screen timeout."));
			UI::sleep();
		}
	}
	// delay(10000);
}
