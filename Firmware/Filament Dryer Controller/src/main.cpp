#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <u8g2lib.h>

#include "filament.h"
#include "operations.h"
#include "ui.h"
#include "utilities.h"

// Pins
const int pButt	   = 2;		 // PD2
const int pTemp	   = A0;	 // PC0
const int pLedOk   = 12;	 // PB4
const int pLedHeat = 13;	 // PB5
const int pHeater  = 9;		 // PB1
const int pFan	   = 5;		 // PD5 TODO: Move away from OS0.
const int pSda	   = SDA;	 // PC4
const int pScl	   = SCL;	 // PC5

// Config.
const unsigned long pollInterval  = 1000UL * 1;
const unsigned long screenTimeout = 1000UL * 10;
const unsigned long heatTimeout	  = 1000UL * 60 * 5;	// 5 minutes in milliseconds

// Screen
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, pScl, pSda);

Ops ops;

// TODO.
void handleButtonInterrupt() {
	static unsigned long lastDebounceTime = 0;
	unsigned long currentTime			  = millis();

	// Debounce - ignore interrupts for 50ms after the last one
	if (currentTime - lastDebounceTime > 50) {
		ops.setStatus(Ops::Status::ButtonDown);
		lastDebounceTime = currentTime;
	}
}

void setup() {

	pinMode(pButt, INPUT_PULLUP);
	pinMode(pTemp, INPUT);
	pinMode(pLedOk, OUTPUT);
	pinMode(pLedHeat, OUTPUT);
	pinMode(pHeater, OUTPUT);
	pinMode(pFan, OUTPUT);

	u8g2.setI2CAddress(UI::screenAddress);	  // Set the I2C address of the display
	u8g2.setBusClock(400000);				  // Set the I2C bus clock speed to 400kHz
	u8g2.begin();
	// u8g2.setBufferPtr(buf);
	// u8g2.initDisplay();

	attachInterrupt(digitalPinToInterrupt(pButt), handleButtonInterrupt, FALLING);

	ops.screenWakeTime = millis();
	u8g2.setPowerSave(0);
	ops.setStatus(Ops::Status::ScreenAwake);

	ops.setStatus(Ops::Status::Ok);
	// Set everything dirty to make it all
	ops.setDirty(Ops::Dirty::All);	  // Set everything dirty to make it all dirty
}

void loop() {
	unsigned long currentTime = millis();

	digitalWrite(pLedOk, ops.getStatus(Ops::Status::Ok));

	// Read sensors.
	if (currentTime >= ops.lastPollTime + pollInterval) {
		ops.lastPollTime = currentTime;

		OutTemp outTemp = analogRead(pTemp);
		if (outTemp != ops.outTemp) {
			ops.outTemp = outTemp;
		}

		int inTemperature = 20 + random(2);	   // TODO: get the temperature sensor value
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

	if (ops.getStatus(Ops::Status::ScreenAwake) &&
		currentTime >= ops.screenWakeTime + screenTimeout) {
		// Turn off the display if it has been idle for too long
		// ops.clearStatus(Ops::Status::ScreenAwake);
		// u8g2.setPowerSave(1);	 // Set power save mode
		// TODO: Delete and uncomment the previous line.
		ops.setStatus(Ops::Status::Select);
		ops.setDirty(Ops::Dirty::Top);
		ops.setDirty(Ops::Dirty::Bottom);
	}

	if (ops.getStatus(Ops::Status::ScreenAwake)) {

		u8g2.clearBuffer();
		u8g2.setFontMode(1);

		if (ops.getStatus(Ops::Status::Select)) {
			UI::drawBorderTop(u8g2);	   // Draw the top border
			UI::drawBorderBottom(u8g2);	   // Draw the top border
		}

		UI::drawFilamentType(u8g2, ops.filament.name);
		UI::drawFilamentTemperature(u8g2, ops.filament.temperature);
		UI::drawFilamentHumidity(u8g2, ops.filament.humidity);

		UI::drawTemperature(u8g2, ops.inTemperature);
		UI::drawHumidity(u8g2, ops.humidity);

		if (ops.getDirty(Ops::Dirty::All)) {
			// If everything is dirty, update the whole screen..
			u8g2.sendBuffer();
			ops.clearAllDirties();
		} else {
			// ..otherwise, just the bits that have changed.
			if (ops.getDirty(Ops::Dirty::Top)) {
				u8g2.updateDisplayArea(0, 0, u8g2.getBufferTileWidth(), 2);
				ops.clearDirty(Ops::Dirty::Top);
			}
			if (ops.getDirty(Ops::Dirty::Bottom)) {
				u8g2.updateDisplayArea(
					0, u8g2.getDisplayHeight() / 8 - 2, u8g2.getBufferTileWidth(), 2
				);
				ops.clearDirty(Ops::Dirty::Bottom);
			}
			if (ops.getDirty(Ops::Dirty::Temp) && !ops.getStatus(Ops::Status::Select)) {
				u8g2.updateDisplayArea(0, 3, u8g2.getBufferTileWidth() / 2, 4);
				ops.clearDirty(Ops::Dirty::Temp);
			}
			if (ops.getDirty(Ops::Dirty::Humidity) && !ops.getStatus(Ops::Status::Select)) {
				u8g2.updateDisplayArea(
					u8g2.getBufferTileWidth() / 2 - 1, 3, u8g2.getBufferTileWidth() / 2, 4
				);
				ops.clearDirty(Ops::Dirty::Humidity);
			}
		}

		/*
		delay(5000);	// Delay for 1 second
		ops.toggleStatus(Ops::Status::Select);

		u8g2.clearBuffer();
		u8g2.setFontMode(1);

		if (ops.getStatus(Ops::Status::Select)) {
			UI::drawBorderTop(u8g2);	   // Draw the top border
			UI::drawBorderBottom(u8g2);	   // Draw the top border
		}

		UI::drawFilamentType(u8g2, "TPU");
		UI::drawFilamentTemperature(u8g2, ops.filament.temperature + 10);
		UI::drawFilamentHumidity(u8g2, ops.filament.humidity + 10);

		UI::drawTemperature(u8g2, ops.inTemperature + 10);
		UI::drawHumidity(u8g2, ops.humidity + 10);

		u8g2.updateDisplayArea(0, 0, u8g2.getDisplayWidth() / 8, 2);
		// u8g2.sendBuffer();

		delay(5000);
		*/
	}
}
