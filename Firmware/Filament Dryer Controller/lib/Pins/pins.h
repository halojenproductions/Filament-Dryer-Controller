#ifndef PINS_H
#define PINS_H

#include <Arduino.h>
#include <stdint.h>

// Pin definitions for Filament Dryer Controller
namespace Pins {
	constexpr uint8_t pButt	   = 2;		 // PD2
	constexpr uint8_t pTemp	   = A0;	 // PC0
	constexpr uint8_t pLedOk   = 12;	 // PB4
	constexpr uint8_t pLedHeat = 13;	 // PB5
	constexpr uint8_t pHeater  = 9;		 // PB1
	constexpr uint8_t pFan	   = 5;		 // PD5 TODO: Move away from OS0.
	constexpr uint8_t pSda	   = SDA;	 // PC4
	constexpr uint8_t pScl	   = SCL;	 // PC5

	inline void setupPins() {
		pinMode(pButt, INPUT_PULLUP);
		pinMode(pTemp, INPUT);
		pinMode(pLedOk, OUTPUT);
		pinMode(pLedHeat, OUTPUT);
		pinMode(pHeater, OUTPUT);
		pinMode(pFan, OUTPUT);
	}
}

#endif
