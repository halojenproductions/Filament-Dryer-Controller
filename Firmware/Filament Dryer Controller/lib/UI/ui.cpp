#include "ui.h"
#include <u8g2lib.h>

namespace UI {
	// OLED address.
	const int screenAddress = 0x78;

	const int borderHeight = 12;	// Height of the top and bottom borders.
	const int padding	   = 2;		// Padding for the text.

	// Filament.
	const uint8_t *filamentFont = u8g2_font_luBS08_tf;

	// Current.
	const uint8_t *currentFont = u8g2_font_luRS19_tf;

	// Error
	const int ERROR_X = 0;
	const int ERROR_Y = 63;

	void drawBorderTop(U8G2_SH1106_128X64_NONAME_F_HW_I2C &screen) {
		screen.setDrawColor(1);
		screen.drawBox(0, 0, screen.getDisplayWidth(), borderHeight);
	}

	void drawBorderBottom(U8G2_SH1106_128X64_NONAME_F_HW_I2C &screen) {
		screen.setDrawColor(1);
		screen.drawBox(
			0,
			screen.getDisplayHeight() - borderHeight,
			screen.getDisplayWidth(),
			screen.getDisplayHeight()
		);
	}

	void drawFilamentType(U8G2_SH1106_128X64_NONAME_F_HW_I2C &screen, String text) {
		screen.setDrawColor(2);
		screen.setFont(filamentFont);
		screen.setFontPosTop();
		screen.setCursor(padding, padding - 1);
		screen.print(text);
	}

	void drawFilamentTemperature(U8G2_SH1106_128X64_NONAME_F_HW_I2C &screen, int temp) {
		screen.setDrawColor(2);
		screen.setFont(filamentFont);
		screen.setFontPosBaseline();
		screen.setCursor(padding, screen.getDisplayHeight() - padding);

		String text = String(temp, 10);
		screen.print(String(text + "\xBA"));
	}

	void drawFilamentHumidity(U8G2_SH1106_128X64_NONAME_F_HW_I2C &screen, int hum) {
		screen.setDrawColor(2);
		screen.setFont(filamentFont);
		screen.setFontPosBaseline();

		String text = String(hum, 10);
		text		= String(text + "%");

		int textWid = screen.getStrWidth(text.c_str());
		screen.setCursor(
			screen.getDisplayWidth() - textWid - padding, screen.getDisplayHeight() - padding
		);

		screen.print(text);
	}

	void drawTemperature(U8G2_SH1106_128X64_NONAME_F_HW_I2C &screen, int temp) {
		screen.setDrawColor(2);
		screen.setFont(currentFont);
		screen.setFontPosCenter();
		screen.setCursor(padding, screen.getDisplayHeight() / 2 - screen.getDescent() / 2 + 1);

		String text = String(temp, 10);
		screen.print(String(text + "\xBA"));
	}

	void drawHumidity(U8G2_SH1106_128X64_NONAME_F_HW_I2C &screen, int hum) {
		screen.setDrawColor(2);
		screen.setFont(currentFont);
		screen.setFontPosCenter();

		String text = String(hum, 10);
		text		= String(text + "%");

		int textWid = screen.getStrWidth(text.c_str());
		screen.setCursor(
			screen.getDisplayWidth() - textWid - padding,
			screen.getDisplayHeight() / 2 - screen.getDescent() / 2 + 1
		);

		screen.print(text);
	}
}
