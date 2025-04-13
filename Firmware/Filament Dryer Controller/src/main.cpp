#include <Adafruit_GFX.h>
#include <Arduino.h>
#include <u8g2lib.h> // Include the u8g2 library for graphics
// put function declarations here:
int myFunction(int, int);

// Pins
const int pButt = 2;	 // PD2
const int pTemp = A0;	 // PC0
const int pLedOk = 12;	 // PB4
const int pLedHeat = 13; // PB5
const int pHeater = 9;	 // PB1
const int pFan = 5;	  // PD5 The PWM outputs generated on pins 5 and 6 will have
					  // higher-than-expected duty cycles.
const int pSda = SDA; // PC4
const int pScl = SCL; // PC5

// Screen
#define SCREEN_WIDTH 128		// OLED display width, in pixels.
#define SCREEN_HEIGHT 64		// OLED display height, in pixels.
const int screenAddress = 0x78; //
U8G2_SH1106_128X64_NONAME_2_SW_I2C u8g2(U8G2_R0, pScl, pSda);

void setup() {
	pinMode(pButt, INPUT_PULLUP);
	pinMode(pTemp, INPUT);
	pinMode(pLedOk, OUTPUT);
	pinMode(pLedHeat, OUTPUT);
	pinMode(pHeater, OUTPUT);
	pinMode(pFan, OUTPUT);

	u8g2.setI2CAddress(screenAddress); // Set the I2C address of the display
	u8g2.begin();

	// put your setup code here, to run once:
	int result = myFunction(2, 3);
}

void loop() {
	int val = analogRead(pTemp); // Read the temperature sensor value
	u8g2.firstPage();
	do {
		u8g2.setFont(u8g2_font_luBS24_tr);
		u8g2.setFontPosBottom();
		u8g2.setCursor(0, 28);
		u8g2.print(val);
		u8g2.drawStr(0, 63, "( .Y. )"); // Draw the string at (0, 20)
	} while (u8g2.nextPage());

	delay(1000);

	// turn the LED on (HIGH is the voltage level)
	digitalWrite(LED_BUILTIN, HIGH);

	// wait for a second
	delay(1000);

	// turn the LED off by making the voltage LOW
	digitalWrite(LED_BUILTIN, LOW);

	// wait for a second
	delay(1000);
}

// put function definitions here:
int myFunction(int x, int y) { return x + y; }