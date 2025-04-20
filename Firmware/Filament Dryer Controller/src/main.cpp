#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <u8g2lib.h>

#include "button.h"
#include "filaments.h"
#include "operations.h"
#include "ui.h"
#include "utilities.h"

#define DEBUG_MODE 0

// Pins
constexpr uint8_t pButt	   = 2;		 // PD2
constexpr uint8_t pTemp	   = A0;	 // PC0
constexpr uint8_t pLedOk   = 12;	 // PB4
constexpr uint8_t pLedHeat = 13;	 // PB5
constexpr uint8_t pHeater  = 9;		 // PB1
constexpr uint8_t pFan	   = 5;		 // PD5 TODO: Move away from OS0.
constexpr uint8_t pSda	   = SDA;	 // PC4
constexpr uint8_t pScl	   = SCL;	 // PC5

// // Screen
// U8G2_SH1106_128X64_NONAME_F_HW_I2C screen(U8G2_R0, pScl, pSda);
// extern U8G2_SH1106_128X64_NONAME_F_HW_I2C screen;

Ops& ops			 = Ops::getInstance();
Filaments& filaments = Filaments::getInstance();

uint32_t currentTime = millis();

void setup() {

	pinMode(pButt, INPUT_PULLUP);
	pinMode(pTemp, INPUT);
	pinMode(pLedOk, OUTPUT);

	pinMode(pLedHeat, OUTPUT);
	digitalWrite(pLedHeat, HIGH);

	pinMode(pHeater, OUTPUT);
	pinMode(pFan, OUTPUT);

	UI::screen.setI2CAddress(0x78);	   // Set the I2C address of the display
	UI::screen.setBusClock(400000);	   // Set the I2C bus clock speed to 400kHz
	UI::screen.begin();

	attachInterrupt(digitalPinToInterrupt(pButt), handleButtonInterrupt, CHANGE);

	// TODO: Load saved settings from EEPROM.

	ops.setCommand(Ops::Command::WakeUp);
	ops.setStatus(Ops::Status::Ok);
	digitalWrite(pLedOk, ops.getStatus(Ops::Status::Ok));
}

void wakeUp() {
	ops.clearCommand(Ops::Command::WakeUp);
	UI::screen.setPowerSave(0);
	ops.setDirty(Ops::Dirty::All);
	ops.setStatus(Ops::Status::ScreenAwake);
	ops.screenTimeout.reset();
};

void sleep() {
	UI::screen.setPowerSave(1);
	ops.clearStatus(Ops::Status::ScreenAwake);
	ops.clearStatus(Ops::Status::Select);
};

void loop() {
	currentTime = millis();
	// TODO: tweak the order of operations later.

	// Wrangle interruption.
	if (interrupted()) {
		// Button changed state. Go and deal with that.
		buttonInterruption();
	}

	// Wake up.
	if (ops.getCommand(Ops::Command::WakeUp)) {
		wakeUp();
	}

	// Button held.
	if (ops.getStatus(Ops::Status::ButtonDown) && ops.buttonHold.get(currentTime) &&
		!ops.getCommand(Ops::Command::ButtonHoldHandled)) {
		buttonHeld();
	}

	// Button clicked.
	if (ops.getCommand(Ops::Command::ButtonClick)) {
		buttonClicked();
	}

	// Read sensors.
	if (ops.inputPolling.check(currentTime)) {
		OutTemp outTemp = analogRead(pTemp);
		if (outTemp != ops.outTemp) {
			ops.outTemp = outTemp;
		}

		int inTemperature = -20 + random(2);	// TODO: get the temperature sensor value
		if (inTemperature != ops.inTemperature) {
			ops.inTemperature = inTemperature;
			ops.setDirty(Ops::Dirty::Temp);
		}

		int humidity = 50 + random(2);	  // TODO: get the humidity sensor value
		if (true || humidity != ops.humidity) {
			ops.humidity = humidity;
			ops.setDirty(Ops::Dirty::Humidity);
		}
	}

	// Set statuses. or should that be commands?
	// TODO.
	if (ops.getStatus(Ops::Status::Error)) {
	};

	if (ops.getStatus(Ops::Status::Heating)) {
	};

	// TODO.
	if (ops.getStatus(Ops::Status::ButtonDown)) {
		// TODO: Handle button press.
	};

	// Execute commands.

	// Update display.

	if (ops.getStatus(Ops::Status::ScreenAwake)) {
		// Load the display buffer.
		UI::screen.clearBuffer();
		UI::screen.setFontMode(1);

#if DEBUG_MODE
		UI::drawAreaBorders(u8g2);		  // Draw the area borders
		ops.setDirty(Ops::Dirty::All);	  // Mark all areas as dirty
#endif

		if (ops.getStatus(Ops::Status::Select)) {
			UI::drawBorderTop();	   // Draw the top border
			UI::drawBorderBottom();	   // Draw the bottom border
		}

		UI::drawFilamentType(filaments.getDisplay().name);
		UI::drawFilamentTemperature(filaments.getDisplay().temperature);
		UI::drawFilamentHumidity(filaments.getDisplay().humidity);

		UI::drawTemperature(ops.inTemperature);
		UI::drawHumidity(ops.humidity);

		// Send the display buffer (or just bits of it).
		UI::updateScreen();
	}

	// Selection timeout.
	if (ops.getStatus(Ops::Status::Select) && ops.selectionTimeout.check(currentTime)) {
		ops.clearStatus(Ops::Status::Select);
		filaments.cancel();
		ops.setDirty(Ops::Dirty::Filament);
	}

	// Screen timeout.
	if (ops.getStatus(Ops::Status::ScreenAwake) && !ops.getStatus(Ops::Status::ButtonDown) &&
		ops.screenTimeout.check(currentTime)) {
		sleep();
	}
}
