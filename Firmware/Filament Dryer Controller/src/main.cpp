#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <u8g2lib.h>

#include "button.h"
#include "filaments.h"
#include "ht.h"
#include "operations.h"
#include "ui.h"

#define DEBUG_MODE 0

// Pins
constexpr byte pButt	= 2;	  // PD2
constexpr byte pTemp	= A0;	  // PC0
constexpr byte pLedOk	= 12;	  // PB4
constexpr byte pLedHeat = 13;	  // PB5
constexpr byte pHeater	= 9;	  // PB1
constexpr byte pFan		= 5;	  // PD5 TODO: Move away from OS0.
constexpr byte pSda		= SDA;	  // PC4
constexpr byte pScl		= SCL;	  // PC5

Ops& ops			 = Ops::getInstance();
Filaments& filaments = Filaments::getInstance();

uint32_t currentTime = millis();

void setup() {
	// Set up pins.
	pinMode(pButt, INPUT_PULLUP);
	pinMode(pTemp, INPUT);
	pinMode(pLedOk, OUTPUT);
	pinMode(pLedHeat, OUTPUT);
	pinMode(pHeater, OUTPUT);
	pinMode(pFan, OUTPUT);

	// TODO move to a setup method in HT.
	// Set up humidity & temperature sensor.
	if (!HT::sensor.begin(0x44)) {
		ops.setStatus(Ops::Status::Error);
	}

	// Set up oled display.
	UI::setup();

	// Set up button interrupt.
	attachInterrupt(digitalPinToInterrupt(pButt), interruptHandler, CHANGE);

	// Set initial values.
	ops.setCommand(Ops::Command::ButtonHoldHandled);
	ops.setCommand(Ops::Command::WakeUp);
	ops.setStatus(Ops::Status::Ok);
	digitalWrite(pLedOk, ops.getStatus(Ops::Status::Ok));
}

void loop() {
	currentTime = millis();

	// Wrangle interruption.
	if (interrupted()) {
		// Button changed state. Go and deal with that.
		interruptAnalyser();
	}

	// Wake up.
	if (ops.checkCommand(Ops::Command::WakeUp)) {
		UI::wakeUp();
	}

	// Button held.
	if (ops.getStatus(Ops::Status::ButtonDown)
		&& ops.buttonHold.get(currentTime)
		&& !ops.getCommand(Ops::Command::ButtonHoldHandled)) {
		buttonHeld();
	}

	// Button clicked.
	if (ops.checkCommand(Ops::Command::ButtonClick)) {
		buttonClicked();
	}

	// Read sensors.
	if (ops.inputPolling.check(currentTime)) {
		ops.checkTherm(Thermistor::adcToCelsius(analogRead(pTemp)));

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
		if (ops.getStatus(Ops::Status::Select) && ops.selectionTimeout.check(currentTime)) {
			ops.clearStatus(Ops::Status::Select);
			filaments.cancel();
			ops.setDirty(Ops::Dirty::Filament);
		}

		// Screen timeout.
		if (!ops.getStatus(Ops::Status::ButtonDown) && ops.screenTimeout.check(currentTime)) {
			UI::sleep();
		}
	}
}
