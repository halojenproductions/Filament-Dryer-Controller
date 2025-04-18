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

// Screen
U8G2_SH1106_128X64_NONAME_2_SW_I2C u8g2(U8G2_R0, pScl, pSda);

Ops ops;

// TODO.
void handleButtonInterrupt() {
	static unsigned long lastDebounceTime = 0;
	unsigned long currentTime			  = millis();

	// Debounce - ignore interrupts for 50ms after the last one
	if (currentTime - lastDebounceTime > 50) {
		ops.setStatus(Ops::ButtonDown);
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
	u8g2.begin();

	attachInterrupt(digitalPinToInterrupt(pButt), handleButtonInterrupt, FALLING);

	ops.setStatus(Ops::Status::Ok);	   // Set the initial status to OK
}

void loop() {
	digitalWrite(pLedOk, ops.getStatus(Ops::Status::Ok));

	// Read inputs.
	ops.outTemp = (int)753;
	// ops.outTemp = analogRead(pTemp);	// Read the temperature sensor value

	// Set statuses.
	// TODO.
	if (ops.getStatus(Ops::Status::Error)) {
	};

	if (ops.getStatus(Ops::Status::Heating)) {
	};

	// TODO.
	if (ops.getStatus(Ops::ButtonDown)) {
		// TODO: Handle button press.
	};

	// Execute commands.

	int val = ops.outTemp;	  // Read the temperature sensor value
	u8g2.firstPage();
	do {
		u8g2.setFontMode(1);

		UI::drawBorderTop(u8g2);	// Draw the top border
		UI::drawFilamentType(u8g2, ops.filament.name);

		UI::drawBorderBottom(u8g2);	   // Draw the top border
		UI::drawFilamentTemperature(u8g2, ops.filament.temperature);
		UI::drawFilamentHumidity(u8g2, ops.filament.humidity);

	} while (u8g2.nextPage());

	delay(1000);	// Delay for 1 second
}
