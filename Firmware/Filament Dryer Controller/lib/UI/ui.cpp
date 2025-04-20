#include "ui.h"

namespace UI {
	Ops& ops = Ops::getInstance();

	U8G2_SH1106_128X64_NONAME_F_HW_I2C screen(U8G2_R0);

	// Filament.
	const uint8_t* filamentFont = u8g2_font_luBS08_tf;

	// Current.
	const uint8_t* currentFont = u8g2_font_luRS19_tf;

	static constexpr byte borderHeight = 12;
	static constexpr byte padding	   = 2;

	// Screen dimensions.
	static constexpr byte pxWidth	  = 128;	// 128 pixels.
	static constexpr byte pxHeight	  = 64;		// 64 pixels.
	static constexpr byte tilesWidth  = 16;		// (8x8 pixels).
	static constexpr byte tilesHeight = 8;		// (8x8 pixels).

	// Zones.
	constexpr Area areaTop		= {0, 0, tilesWidth, 2};
	constexpr Area areaBottom	= {0, tilesHeight - 2, tilesWidth, 2};
	constexpr Area areaTemp		= {0, 2, tilesWidth / 2, 4};
	constexpr Area areaHumidity = {tilesWidth / 2, 2, tilesWidth / 2, 4};

	void updateScreen() {
		if (ops.getDirty(Ops::Dirty::All)) {
			// If everything is dirty, update the whole screen..
			screen.sendBuffer();
			ops.clearAllDirties();
		} else {
			// ..otherwise, just the bits that have changed.
			if (ops.getDirty(Ops::Dirty::Filament)) {
				areaTop.updateArea(screen);
				areaBottom.updateArea(screen);
				ops.clearDirty(Ops::Dirty::Filament);
			}
			// Deliberately not updating the live readouts (temp and hum) while in selection
			// mode.
			if (!ops.getStatus(Ops::Status::Select)) {
				if (ops.getDirty(Ops::Dirty::Temp)) {
					areaTemp.updateArea(screen);
					ops.clearDirty(Ops::Dirty::Temp);
				}
				if (ops.getDirty(Ops::Dirty::Humidity)) {
					areaHumidity.updateArea(screen);
					ops.clearDirty(Ops::Dirty::Humidity);
				}
			}
		}
	}

	void updateAreaFil() {
		// screen.updateDisplayArea(areaTop.x, areaTop.y, areaTop.w, areaTop.h);
		areaTop.updateArea(screen);
	}

	void drawBorderTop() {
		screen.setDrawColor(1);
		screen.drawBox(0, 0, screen.getDisplayWidth(), borderHeight);
	}

	void drawBorderBottom() {
		screen.setDrawColor(1);
		screen.drawBox(
			0,
			screen.getDisplayHeight() - borderHeight,
			screen.getDisplayWidth(),
			screen.getDisplayHeight()
		);
	}

	void drawFilamentType(const char* text) {
		screen.setDrawColor(2);
		screen.setFont(filamentFont);
		screen.setFontPosTop();
		screen.setCursor(padding, padding - 1);
		screen.print(text);
	}

	void drawFilamentTemperature(int temp) {
		screen.setDrawColor(2);
		screen.setFont(filamentFont);
		screen.setFontPosBaseline();
		screen.setCursor(padding, screen.getDisplayHeight() - padding);

		String text = String(temp, 10);
		screen.print(String(text + "\xBA"));
	}

	void drawFilamentHumidity(int hum) {
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

	void drawTemperature(int temp) {
		screen.setDrawColor(2);
		screen.setFont(currentFont);
		screen.setFontPosCenter();
		screen.setCursor(padding, screen.getDisplayHeight() / 2 - screen.getDescent() / 2 + 1);

		String text = String(temp, 10);
		screen.print(String(text + "\xBA"));
	}

	void drawHumidity(int hum) {
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

	void drawAreaBorders() {
		screen.setDrawColor(1);
		// draw top area
		screen.drawFrame(areaTop.x * 8, areaTop.y * 8, areaTop.w * 8, areaTop.h * 8);
		// draw bottom area
		screen.drawFrame(areaBottom.x * 8, areaBottom.y * 8, areaBottom.w * 8, areaBottom.h * 8);
		// draw temp area
		screen.drawFrame(areaTemp.x * 8, areaTemp.y * 8, areaTemp.w * 8, areaTemp.h * 8);
		// draw humidity area
		screen.drawFrame(
			areaHumidity.x * 8, areaHumidity.y * 8, areaHumidity.w * 8, areaHumidity.h * 8
		);
	}
}
