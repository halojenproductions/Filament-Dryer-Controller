#ifndef PINS_H
#define PINS_H

#include <Arduino.h>
#include <stdint.h>

// Pin definitions for Filament Dryer Controller
namespace Pins {
	constexpr uint8_t pButt	   = 2;		 // PD2 Internal pullup.
	constexpr uint8_t pTemp	   = A0;	 // PC0 External pulldown.
	constexpr uint8_t pLedOk   = 12;	 // PB4 Active high.
	constexpr uint8_t pLedHeat = 13;	 // PB5 Active high.
	constexpr uint8_t pHeater  = 9;		 // PB1 Active low.
	constexpr uint8_t pFan	   = 5;		 // PD5 PWM TODO: Move away from OS0.
	constexpr uint8_t pSda	   = SDA;	 // PC4
	constexpr uint8_t pScl	   = SCL;	 // PC5

	inline void setupPins() {
		pinMode(pButt, INPUT_PULLUP);
		pinMode(pTemp, INPUT);
		pinMode(pLedOk, OUTPUT);
		pinMode(pLedHeat, OUTPUT);
		pinMode(pHeater, OUTPUT);
		pinMode(pFan, OUTPUT);

		digitalWrite(Pins::pLedHeat, LOW);
		digitalWrite(Pins::pHeater, HIGH);
		analogWrite(Pins::pFan, 0);
	}
}

#endif
