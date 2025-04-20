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

	static constexpr int screenAddress = 0x78;

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
	extern void drawAreaBorders(U8G2_SH1106_128X64_NONAME_F_HW_I2C& screen);
	extern void drawBorderTop(U8G2_SH1106_128X64_NONAME_F_HW_I2C& screen);
	extern void drawBorderBottom(U8G2_SH1106_128X64_NONAME_F_HW_I2C& screen);
	extern void drawFilamentType(U8G2_SH1106_128X64_NONAME_F_HW_I2C& screen, String text);
	extern void drawFilamentTemperature(U8G2_SH1106_128X64_NONAME_F_HW_I2C& screen, int temp);
	extern void drawFilamentHumidity(U8G2_SH1106_128X64_NONAME_F_HW_I2C& screen, int hum);
	extern void drawTemperature(U8G2_SH1106_128X64_NONAME_F_HW_I2C& screen, int temp);
	extern void drawHumidity(U8G2_SH1106_128X64_NONAME_F_HW_I2C& screen, int hum);

}
#endif
