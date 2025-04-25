#ifndef UI_H
#define UI_H

#include "filaments.h"
#include "operations.h"
#include <u8g2lib.h>

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
	extern Filaments& filaments;

	extern U8G2_SH1106_128X64_NONAME_F_HW_I2C screen;

	// Functions.
	extern void setupScreen();
	extern void wakeUp();
	extern void sleep();

	extern void updateScreen();

	extern void drawAll();

	extern void drawBorderTop();
	extern void drawBorderBottom();

	extern void drawFilamentName(const char* text);
	extern void drawFilamentHumidity(uint8_t hum);
	extern void drawFilamentTemp(uint8_t temp);

	extern void drawRealtimeHumidity(uint8_t hum);
	extern void drawRealtimeTemp(uint8_t temp);

	extern void drawAreaBorders();
}

#endif
