#include "filaments.h"
#include <u8g2lib.h>

#ifndef UI_H
#define UI_H

namespace UI {
	struct Area {
		byte x;
		byte y;
		byte w;
		byte h;
	};

	extern U8G2_SH1106_128X64_NONAME_F_HW_I2C screen;

	// Filament
	extern const uint8_t* filamentFont;

	// Current
	extern const uint8_t* currentFont;

	// Error
	extern const int ERROR_X;
	extern const int ERROR_Y;

	// Zones.
	extern const Area areaTop;
	extern const Area areaBottom;
	extern const Area areaTemp;
	extern const Area areaHumidity;

	// Functions.
	extern void drawAreaBorders();
	extern void drawBorderTop();
	extern void drawBorderBottom();
	extern void drawFilamentType(String text);
	extern void drawFilamentTemperature(int temp);
	extern void drawFilamentHumidity(int hum);
	extern void drawTemperature(int temp);
	extern void drawHumidity(int hum);

}
#endif
