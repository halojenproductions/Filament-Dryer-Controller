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

	// Functions.
	extern void updateScreen();

	extern void drawAll();

	extern void drawBorderTop();
	extern void drawBorderBottom();
	extern void drawFilamentType(const char* text);
	extern void drawFilamentTemp(int temp);
	extern void drawFilamentHumidity(int hum);
	extern void drawRealtimeTemp(int temp);
	extern void drawRealtimeHumidity(int hum);
	extern void drawAreaBorders();

}
#endif
