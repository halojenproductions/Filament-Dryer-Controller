#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <u8g2lib.h>

#include "button.h"
#include "controlLoop.h"
#include "filaments.h"
#include "ht.h"
#include "operations.h"
#include "pins.h"
#include "ui.h"

#define DEBUG_MODE 0

Ops& ops			 = Ops::getInstance();
Filaments& filaments = Filaments::getInstance();


void setup() {
	ops.currentTime = millis();

	// Set up pins.
	Pins::setup();

	// TODO move to a setup method in HT.
	// Set up humidity & temperature sensor.
	if (!HT::sensor.begin(0x44)) {
		ops.setStatus(Ops::Status::Error); // TODO handle error.
	}

	// Set up oled display.
	UI::setup();

	// Set up button interrupt.
	attachInterrupt(digitalPinToInterrupt(Pins::pButt), Button::interruptHandler, CHANGE);

	// Set initial values.
	ops.setCommand(Ops::Command::ButtonHoldHandled);
	ops.setCommand(Ops::Command::WakeUp);
	ops.setStatus(Ops::Status::Ok);
	digitalWrite(Pins::pLedOk, ops.getStatus(Ops::Status::Ok));
}

void loop() {
	ops.currentTime = millis();

	// Wrangle interruption.
	if (Button::interrupted()) {
		// Button changed state. Go and deal with that.
		Button::interruptAnalyser();
	}

	// Wake up.
	if (ops.checkCommand(Ops::Command::WakeUp)) {
		UI::wakeUp();
	}

	// Button held.
	if (ops.getStatus(Ops::Status::ButtonDown)
		&& ops.buttonHold.get(ops.currentTime)
		&& !ops.getCommand(Ops::Command::ButtonHoldHandled)) {
		Button::buttonHeld();
	}

	// Button clicked.
	if (ops.checkCommand(Ops::Command::ButtonClicked)) {
		Button::buttonClicked();
	}

	// Read sensors.
	if (ops.inputPollingActive.check(ops.currentTime)) {
		ops.checkTherm(Thermistor::adcToCelsius(analogRead(Pins::pTemp)));

		// TODO Remove mocky shit.
		float humidity = 50 + (int)random(2);
		if (ops.checkHumidity(humidity)) {
			// if(ops.checkHumidity(HT::sensor.readHumidity())) {
			ops.setDirty(Ops::Dirty::Humidity);
		}

		// TODO Remove mocky shit.
		float inTemperature = 20 + (int)random(2);
		if (ops.checkTemperature(inTemperature)) {
			// if(ops.checkTemperature(HT::sensor.readTemperature())) {
			ops.setDirty(Ops::Dirty::Temp);
		}
	}
	// TODO Else if status is active, poll exhaust temp every time.

	ControlLoop::controlLoop();

	// Set statuses. or should that be commands?
	if (ops.getStatus(Ops::Status::Error)) {
	}

	if (ops.getStatus(Ops::Status::Heating)) {
	}

	// Update display.
	if (ops.getStatus(Ops::Status::ScreenAwake)) {
		// Load the display buffer.
#if DEBUG_MODE
		UI::drawAreaBorders();			  // Draw the area borders
		ops.setDirty(Ops::Dirty::All);	  // Mark all areas as dirty
#endif
		UI::drawAll();

		// Send the display buffer (or just bits of it).
		UI::updateScreen();

		// Selection timeout.
		if (ops.getStatus(Ops::Status::Select) && ops.selectionTimeout.check(ops.currentTime)) {
			ops.clearStatus(Ops::Status::Select);
			filaments.cancel();
			ops.setDirty(Ops::Dirty::Filament);
		}

		// Screen timeout.
		if (!ops.getStatus(Ops::Status::ButtonDown) && ops.screenTimeout.check(ops.currentTime)) {
			UI::sleep();
		}
	}
}
