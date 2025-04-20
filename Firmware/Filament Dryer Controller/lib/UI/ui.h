#include "filaments.h"
#include "operations.h"
#include <u8g2lib.h>

#ifndef UI_H
#define UI_H

namespace UI {
	struct Area {
		byte x;
		byte y;
		byte w;
		byte h;

		void updateArea(U8G2_SH1106_128X64_NONAME_F_HW_I2C& screen) const {
			screen.updateDisplayArea(x, y, w, h);
		}
	};

	extern Ops& ops;

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
	extern void updateScreen();

	extern void drawBorderTop();
	extern void drawBorderBottom();
	extern void drawFilamentType(const char* text);
	extern void drawFilamentTemperature(int temp);
	extern void drawFilamentHumidity(int hum);
	extern void drawTemperature(int temp);
	extern void drawHumidity(int hum);
	extern void drawAreaBorders();

}
#endif
