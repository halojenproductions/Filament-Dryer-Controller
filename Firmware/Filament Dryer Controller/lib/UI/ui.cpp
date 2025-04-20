#include "ui.h"

namespace UI {
	Ops& ops			 = Ops::getInstance();
	Filaments& filaments = Filaments::getInstance();

	U8G2_SH1106_128X64_NONAME_F_HW_I2C screen(U8G2_R0);

	// Screen dimensions.
	static constexpr byte pxWidth	  = 128;	// 128 pixels.
	static constexpr byte pxHeight	  = 64;		// 64 pixels.
	static constexpr byte tilesWidth  = 16;		// (8x8 pixels).
	static constexpr byte tilesHeight = 8;		// (8x8 pixels).

	// Zones.
	static constexpr Area areaTop	   = {0, 0, tilesWidth, 2};
	static constexpr Area areaBottom   = {0, tilesHeight - 2, tilesWidth, 2};
	static constexpr Area areaTemp	   = {0, 2, tilesWidth / 2, 4};
	static constexpr Area areaHumidity = {tilesWidth / 2, 2, tilesWidth / 2, 4};

	// Layout.
	static constexpr byte borderHeight = 12;
	static constexpr byte padFilX	   = 2;
	static constexpr byte padFilY	   = 2;
	static constexpr byte padRealtimeX = 6;
	static constexpr byte posRealtimeY = pxHeight / 2 + 2;

	// Fonts..
	static const uint8_t* filamentFont = u8g2_font_luBS08_tf;
	static const uint8_t* currentFont  = u8g2_font_luRS19_tf;

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
		screen.clearBuffer();
	}

	void drawAll() {
		UI::screen.setFontMode(1);

		if (ops.getStatus(Ops::Status::Select)) {
			UI::drawBorderTop();
			UI::drawBorderBottom();
		}

		UI::drawFilamentType(filaments.getDisplay().name);
		UI::drawFilamentTemp(filaments.getDisplay().temperature);
		UI::drawFilamentHumidity(filaments.getDisplay().humidity);

		UI::drawRealtimeTemp(ops.inTemperature);
		UI::drawRealtimeHumidity(ops.humidity);
	}

	void drawBorderTop() {
		screen.setDrawColor(1);
		screen.drawBox(0, 0, pxWidth, borderHeight);
	}

	void drawBorderBottom() {
		screen.setDrawColor(1);
		screen.drawBox(0, pxHeight - borderHeight, pxWidth, pxHeight);
	}

	void drawFilamentType(const char* text) {
		screen.setDrawColor(2);
		screen.setFont(filamentFont);
		screen.setFontPosTop();
		screen.setCursor(padFilX, padFilY - 1);
		screen.print(text);
	}

	void drawFilamentTemp(int temp) {
		screen.setDrawColor(2);
		screen.setFont(filamentFont);
		screen.setFontPosBaseline();
		screen.setCursor(padFilX, pxHeight - padFilY);

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
		screen.setCursor(pxWidth - textWid - padFilX, pxHeight - padFilY);

		screen.print(text);
	}

	void drawRealtimeTemp(int temp) {
		screen.setDrawColor(2);
		screen.setFont(currentFont);
		screen.setFontPosCenter();
		screen.setCursor(padRealtimeX, posRealtimeY);

		String text = String(temp, 10);
		screen.print(String(text + "\xBA"));
	}

	void drawRealtimeHumidity(int hum) {
		screen.setDrawColor(2);
		screen.setFont(currentFont);
		screen.setFontPosCenter();

		String text = String(hum, 10);
		text		= String(text + "%");

		int textWid = screen.getStrWidth(text.c_str());
		screen.setCursor(pxWidth - textWid - padRealtimeX, posRealtimeY);

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
