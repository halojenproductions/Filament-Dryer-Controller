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

int freeRam() {
	extern int __heap_start, *__brkval;
	int v;
	return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void printMemoryUsage() {
	Serial.println(F("Memory Usage:"));

	Serial.print(F("Ops singleton: "));
	Serial.println(sizeof(Ops));

	Serial.print(F("Filaments singleton: "));
	Serial.println(sizeof(Filaments));

	Serial.print(F("UI screen: "));
	Serial.println(sizeof(U8G2_SH1106_128X64_NONAME_F_HW_I2C));

	Serial.print(F("HT sensor: "));
	Serial.println(sizeof(Adafruit_SHT31));
}

void setup() {
	// Setup serial write output.
	delay(1000);

	// Set up pins.
	// Serial.println(F("Pins"));
	Pins::setupPins();

	Serial.begin(9600);
	while (!Serial) {	 // Wait for serial port to connect
		delay(10);
	}
	Serial.println(F("Setup start"));

	Serial.print(F("Free RAM before display init: "));
	Serial.println(freeRam());
	printMemoryUsage();

	// Set up oled display.
	// Serial.println("UI");
	UI::setupScreen();
	Serial.println(F("UI setup complete"));

	Serial.print(F("Free RAM after display init: "));
	Serial.println(freeRam());
	printMemoryUsage();

	ops.currentTime = millis();

	// TODO move to a setup method in HT.
	// Set up humidity & temperature sensor.
	if (!HT::sensor.begin(0x44)) {
		// TODO Uncomment when sensor is connected.
		// ops.setStatus(Ops::Status::Error);	  // TODO handle error.
	}
	Serial.println(F("Sensor setup complete"));

	// Set up button interrupt.
	attachInterrupt(digitalPinToInterrupt(Pins::pButt), Button::interruptHandler, CHANGE);
	Serial.println(F("Interrupt attached"));

	// Set initial values.
	ops.setCommand(Ops::Command::ButtonHoldHandled);
	ops.setCommand(Ops::Command::WakeUp);
	ops.setStatus(Ops::Status::Ok);
	digitalWrite(Pins::pLedOk, ops.getStatus(Ops::Status::Ok) ? HIGH : LOW);
	ops.setStatus(Ops::Status::Active);
	Serial.println(F("Initial values set"));
	// ControlLoop::idle();

	// Serial.println(F("Setup finished"));
}

void loop() {
	Serial.println(F("Main loop start"));

	ops.currentTime = millis();
	Serial.println(F("currentTime set"));

	// Wrangle interruption.
	if (Button::interrupted()) {
		Serial.println(F("interruptAnalyser"));
		// Button changed state. Go and deal with that.
		Button::interruptAnalyser();
	}
	// Wake up.
	if (ops.checkCommand(Ops::Command::WakeUp)) {
		Serial.println(F("Command::WakeUp"));
		UI::wakeUp();
		Serial.println(F("Finished WakeUp"));
	}

	// Button held.
	if (ops.getStatus(Ops::Status::ButtonDown)
		// && ops.buttonHold.get(ops.currentTime)
		&& ops.getTimer(Ops::Timers::ButtonHold)
		&& !ops.getCommand(Ops::Command::ButtonHoldHandled)) {
		Serial.println(F("buttonHeld"));
		Button::buttonHeld();
	}

	// Button clicked.
	if (ops.checkCommand(Ops::Command::ButtonClicked)) {
		Serial.println(F("buttonClicked"));
		Button::buttonClicked();
	} else {
		// TODO remove this delay.
		Serial.println(F("Button not clicked"));
	}

	// Read sensors.
	
	if ((ops.getStatus(Ops::Status::Active)
		 // && ops.inputPollingActive.check(ops.currentTime)
		 && ops.checkTimer(Ops::Timers::InputPollingActive))
		|| (!ops.getStatus(Ops::Status::Active)
			// && ops.inputPollingIdle.check(ops.currentTime)
			&& ops.checkTimer(Ops::Timers::InputPollingIdle))) {
		Serial.println(F("Read sensors"));

		/// Check thermistor.
		// TODO Remove mocky shit.
		ops.checkTherm(50);
		// ops.checkTherm(Thermistor::adcToCelsius(analogRead(Pins::pTemp)));

		/// Check humidity.
		// TODO Remove mocky shit.
		float humidity = 50 + (int)random(2);
		if (ops.checkHumidity(humidity)) {
			// if(ops.checkHumidity(HT::sensor.readHumidity())) {
			ops.setDirty(Ops::Dirty::Humidity);
		}

		/// Check temperature.
		// TODO Remove mocky shit.
		float inTemperature = 20 + (int)random(2);
		if (ops.checkTemperature(inTemperature)) {
			// if(ops.checkTemperature(HT::sensor.readTemperature())) {
			ops.setDirty(Ops::Dirty::Temp);
		}
	}
	

	delay(5000);	// TODO remove this delay.
	// return;
	// Control loop.
	/*
	if (ops.getStatus(Ops::Status::Active)) {
		Serial.println(F("active"));
		ControlLoop::active();
	} else {
		Serial.println(F("idle"));
		// ControlLoop::idle();
	}
	*/

	// Set statuses. or should that be commands?
	if (ops.getStatus(Ops::Status::Error)) {
		Serial.println(F("Status::Error"));

		ops.clearStatus(Ops::Status::Ok);
		digitalWrite(Pins::pLedOk, ops.getStatus(Ops::Status::Ok) ? HIGH : LOW);
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
		Serial.println(F("drawAll"));
		UI::drawAll();

		// Send the display buffer (or just bits of it).
		Serial.println(F("updateScreen"));
		UI::updateScreen();

		// Selection timeout.
		if (ops.getStatus(Ops::Status::Select)
			// && ops.selectionTimeout.check(ops.currentTime)
			&& ops.checkTimer(Ops::Timers::SelectionTimeout)) {
			Serial.println(F("Selection timeout"));
			ops.clearStatus(Ops::Status::Select);
			filaments.cancel();
			ops.setDirty(Ops::Dirty::Filament);
		}

		// Screen timeout.
		if (!ops.getStatus(Ops::Status::ButtonDown)
			// && ops.screenTimeout.check(ops.currentTime)
			&& ops.checkTimer(Ops::Timers::ScreenTimeout)) {
			Serial.println(F("Screen timeout."));
			UI::sleep();
		}
	}
}
