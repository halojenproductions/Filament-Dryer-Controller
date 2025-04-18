#include "filament.h"
#include <u8g2lib.h>

#ifndef UI_H
#define UI_H

namespace UI {
	// OLED address
	extern const int screenAddress;

	// Filament type
	extern const int filNameX;
	extern const int filNameY;
	extern const uint8_t *filNameFont;

	// Temperature
	extern const int filTempX;
	extern const int filTempY;
	extern const uint8_t *filTempFont;

	// Filament humidity.
	extern const int filHumidityX;
	extern const int filHumidityY;
	extern const uint8_t *filHumidityFont;

	// Error
	extern const int ERROR_X;
	extern const int ERROR_Y;

	// Functions.
	extern void drawBorderTop(U8G2_SH1106_128X64_NONAME_2_SW_I2C &screen);
	extern void drawBorderBottom(U8G2_SH1106_128X64_NONAME_2_SW_I2C &screen);
	extern void drawFilamentType(U8G2_SH1106_128X64_NONAME_2_SW_I2C &screen, String text);
	extern void drawFilamentTemp(U8G2_SH1106_128X64_NONAME_2_SW_I2C &screen, int temperature);

}
#endif
