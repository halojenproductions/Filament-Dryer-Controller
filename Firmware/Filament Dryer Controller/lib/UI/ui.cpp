#include "ui.h"
#include "filament.h"
#include <u8g2lib.h>

namespace UI {
	// OLED address.
	const int screenAddress = 0x78;

	const int borderHeight = 12;	// Height of the top and bottom borders.

	// Filament name.
	const int filNameX		   = 0;
	const int filNameY		   = 0;
	const uint8_t *filNameFont = u8g2_font_luBS10_tr;

	// Filament temperature.
	const int filTempX		   = 0;
	const int filTempY		   = 28;
	const uint8_t *filTempFont = u8g2_font_luBS10_tf;

	// Filament humidity.
	const int filHumidityX		   = 0;
	const int filHumidityY		   = 28;
	const uint8_t *filHumidityFont = u8g2_font_luBS10_tr;

	// Error
	const int ERROR_X = 0;
	const int ERROR_Y = 63;

	void drawBorderTop(U8G2_SH1106_128X64_NONAME_2_SW_I2C &screen) {
		screen.setDrawColor(1);
		screen.drawBox(0, 0, screen.getDisplayWidth(), borderHeight);
	}

	void drawBorderBottom(U8G2_SH1106_128X64_NONAME_2_SW_I2C &screen) {
		screen.setDrawColor(1);
		screen.drawBox(
			0,
			screen.getDisplayHeight() - borderHeight,
			screen.getDisplayWidth(),
			screen.getDisplayHeight()
		);
	}

	void drawFilamentType(U8G2_SH1106_128X64_NONAME_2_SW_I2C &screen, String text) {
		screen.setFont(filNameFont);
		screen.setFontPosTop();
		screen.setCursor(filNameX, filNameY);
		screen.setDrawColor(2);
		screen.print(text);
	}

	void drawFilamentTemp(U8G2_SH1106_128X64_NONAME_2_SW_I2C &screen, int temperature) {
		screen.setFont(filTempFont);
		screen.setFontPosBottom();
		screen.setCursor(filTempX, filTempY);
		screen.setDrawColor(2);

		String text = String(temperature, 10);
		// screen.print("°");
		screen.print(String(text + "\xB0"));
	}

}
