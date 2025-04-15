#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <u8g2lib.h>

#include "status.h"

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
#define SCREEN_WIDTH 128		   // OLED display width, in pixels.
#define SCREEN_HEIGHT 64		   // OLED display height, in pixels.
const int screenAddress = 0x78;	   //
U8G2_SH1106_128X64_NONAME_2_SW_I2C u8g2(U8G2_R0, pScl, pSda);

Status status;

volatile bool buttonPressed = false;

// TODO.
void handleButtonInterrupt() {
	static unsigned long lastDebounceTime = 0;
	unsigned long currentTime			  = millis();

	// Debounce - ignore interrupts for 50ms after the last one
	if (currentTime - lastDebounceTime > 50) {
		buttonPressed	 = true;
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

	u8g2.setI2CAddress(screenAddress);	  // Set the I2C address of the display
	u8g2.begin();

	attachInterrupt(digitalPinToInterrupt(pButt), handleButtonInterrupt, FALLING);
}

void loop() {
	// TODO.
	if (status.isSet(Status::Error)) {
	};

	// TODO.
	if (buttonPressed) {
		buttonPressed = false;
	};

	int val = analogRead(pTemp);	// Read the temperature sensor value
	u8g2.firstPage();
	do {
		u8g2.setFont(u8g2_font_luBS24_tr);
		u8g2.setFontPosBottom();
		u8g2.setCursor(0, 28);
		u8g2.print(val);
		u8g2.drawStr(0, 63, "( .Y. )");	   // Draw the string at (0, 20)
	} while (u8g2.nextPage());
}
