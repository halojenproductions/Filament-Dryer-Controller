#ifndef UI_H
#define UI_H

#include "Arduino.h"
#include "filaments.h"
#include "system.h"
#include "utilities.h"
#include <Arduino.h>
#include <u8g2lib.h>

namespace UI {
	struct Area {
		byte x;
		byte y;
		byte w;
		byte h;

		void updateArea(U8G2_SH1106_128X64_NONAME_2_HW_I2C& screen) const {
			screen.updateDisplayArea(x, y, w, h);
		}
	};

	extern U8G2_SH1106_128X64_NONAME_2_HW_I2C screen;

	// Functions.
	extern void setupScreen();
	extern void updateScreen_FullFrameBuffer();
	extern void wakeUp();
	extern void sleep();

	extern void updateScreen();

	extern void drawUI();

	extern void drawBorderTop();
	extern void drawBorderBottom();

	extern void drawFilamentName(const char* text);
	extern void drawFilamentHumidity(uint8_t hum);
	extern void drawFilamentTemp(uint8_t temp);

	extern void drawRealtimeHumidity(uint8_t hum);
	extern void drawRealtimeTemp(uint8_t temp);

	extern void drawAreaBorders();

	// Dirty parts.
	enum Dirty : uint8_t {
		All,
		Filament,
		Temp,
		Humidity,
		_Last
	};

	extern byte dirties;

	// Dirty methods.
	void setDirty(Dirty dirty);
	void clearDirty(Dirty dirty);
	bool getDirty(Dirty dirty);
	bool checkDirty(Dirty dirty);
	void clearDirties();

}

#endif
