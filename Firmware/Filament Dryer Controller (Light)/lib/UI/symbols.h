#ifndef SYMBOLS_H
#define SYMBOLS_H

#include <avr/pgmspace.h>

namespace Symbols {
#define Full_width 8
#define Full_height 8
	static const U8X8_PROGMEM byte Full_bits[8] = {
		0b10000010,	   // Reversed from 0b01000001
		0b11010110,	   // Reversed from 0b01101011
		0b10101010,	   // Reversed from 0b01010101
		0b11010110,	   // Reversed from 0b01101011
		0b10101010,	   // Reversed from 0b01010101
		0b11010110,	   // Reversed from 0b01101011
		0b10101010,	   // Reversed from 0b01010101
		0b11111110,	   // Reversed from 0b01111111
	};

#define Heat_width 8
#define Heat_height 8
	static const U8X8_PROGMEM byte Heat_bits[8] = {
		0b00000000,	   // Unchanged from 0b00000000
		0b00100100,	   // Reversed from 0b00100100 (palindrome)
		0b01001000,	   // Reversed from 0b00010010
		0b00100100,	   // Reversed from 0b00100100 (palindrome)
		0b00010010,	   // Reversed from 0b01001000
		0b00100100,	   // Reversed from 0b00100100 (palindrome)
		0b00000000,	   // Unchanged from 0b00000000
		0b01111110,	   // Reversed from 0b01111110 (palindrome)
	};

#define Moist_width 8
#define Moist_height 8
	static const U8X8_PROGMEM byte Moist_bits[8] = {
		0b00001000,	   // Reversed from 0b00010000
		0b00011100,	   // Reversed from 0b00111000
		0b00011100,	   // Reversed from 0b00111000
		0b00111110,	   // Reversed from 0b01111100
		0b00111010,	   // Reversed from 0b01011100
		0b00111010,	   // Reversed from 0b01011100
		0b00111110,	   // Reversed from 0b01111100
		0b00011100,	   // Reversed from 0b00111000
	};

}

#endif
