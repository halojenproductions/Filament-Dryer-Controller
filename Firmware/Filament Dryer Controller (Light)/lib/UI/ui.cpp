#include "ui.h"

namespace UI {

	U8G2_SH1106_128X64_NONAME_2_HW_I2C screen(U8G2_R0);

	void setupScreen() {
		screen.setI2CAddress(0x78);	   // Set the I2C address of the display
		screen.setBusClock(400000);	   // Set the I2C bus clock speed to 400kHz
		screen.begin();

		screen.setFontMode(1);
	}

	void wakeUp() {
		Serial.println(F("UI::wakeUp()"));
		screen.setPowerSave(0);
		Util::setStatus(Sys::Status::ScreenAwake);
		Util::resetTimer(Sys::screenTimeout);
		UI::setDirty(UI::Dirty::All);
	}

	void sleep() {
		screen.setPowerSave(1);
		Util::clearStatus(Sys::Status::ScreenAwake);
		Filaments::cancel();
		Util::clearStatus(Sys::Status::Select);
	}

	// Screen dimensions.
	static constexpr byte pxWidth	  = 128;	// 128 pixels.
	static constexpr byte pxHeight	  = 64;		// 64 pixels.
	static constexpr byte tilesWidth  = 16;		// (8x8 pixels).
	static constexpr byte tilesHeight = 8;		// (8x8 pixels).

	// Zones.
	static constexpr Area areaTop	   = {0, 0, tilesWidth, 2};
	static constexpr Area areaBottom   = {0, tilesHeight - 2, tilesWidth, 2};
	static constexpr Area areaHumidity = {0, 2, tilesWidth / 2, 4};
	static constexpr Area areaTemp	   = {tilesWidth / 2, 2, tilesWidth / 2, 4};

	void updateScreen() {
		// Serial.println(F("UI::updateScreen()"));
		screen.firstPage();
		do {
			drawUI();
		} while (screen.nextPage());
	}

	void updateScreen_FullFrameBuffer() {
		// Serial.println(F("UI::updateScreen()"));
		if (checkDirty(UI::Dirty::All)) {
			// If everything is dirty, update the whole screen.
			screen.sendBuffer();
			clearDirties();
		} else {
			// ..otherwise, just the bits that have changed.
			if (checkDirty(UI::Dirty::Filament)) {
				areaTop.updateArea(screen);
				areaBottom.updateArea(screen);
			}
			// Don't update the realtime bits while in selection mode.
			if (!Util::getStatus(Sys::Status::Select)) {
				if (checkDirty(UI::Dirty::Temp)) {
					areaTemp.updateArea(screen);
				}
				if (checkDirty(UI::Dirty::Humidity)) {
					areaHumidity.updateArea(screen);
				}
			}
		}
		screen.clearBuffer();
	}

	// Layout.
	static constexpr byte borderHeight = 12;
	static constexpr byte padFilX	   = 2;
	static constexpr byte padFilY	   = 2;
	static constexpr byte padRealtimeX = 6;
	static constexpr byte posRealtimeY = pxHeight / 2 + 2;

	// Fonts.
	static const uint8_t* filamentFont = u8g2_font_luBS08_tf;
	static const uint8_t* realtimeFont = u8g2_font_luRS19_tf;

	void drawUI() {
		// Serial.println(F("UI::drawUI()"));
		screen.setFontMode(1);

		if (Util::getStatus(Sys::Status::Select)) {
			drawBorderTop();
			drawBorderBottom();
		}

		drawFilamentName(Filaments::displayFilament.name);
		drawFilamentTemp(Filaments::displayFilament.temperature);
		drawFilamentHumidity(Filaments::displayFilament.humidity);

		drawRealtimeTemp(Sys::sensTemp);
		drawRealtimeHumidity(Sys::sensHumid);
	}

	void drawBorderTop() {
		screen.setDrawColor(1);
		screen.drawBox(0, 0, pxWidth, borderHeight);
	}

	void drawBorderBottom() {
		screen.setDrawColor(1);
		screen.drawBox(0, pxHeight - borderHeight, pxWidth, pxHeight);
	}

	void drawFilamentName(const char* text) {
		screen.setDrawColor(2);
		screen.setFont(filamentFont);
		screen.setFontPosTop();
		screen.setCursor(padFilX, padFilY - 1);
		screen.print(text);
	}

	void drawFilamentHumidity(uint8_t hum) {
		screen.setDrawColor(2);
		screen.setFont(filamentFont);
		screen.setFontPosBaseline();

		// String text = String(hum, 10);
		// text		= String(text + "%");

		char buffer[5];	   // Space for "100%\0"
		snprintf(buffer, sizeof(buffer), "%d%%", hum);

		screen.setCursor(padFilX, pxHeight - padFilY);
		screen.print(buffer);
	}

	void drawFilamentTemp(uint8_t temp) {
		screen.setDrawColor(2);
		screen.setFont(filamentFont);
		screen.setFontPosBaseline();

		// String text = String(temp, 10);
		// text		= String(text + "\xBA");

		char buffer[5];	   // Space for "100%\0"
		snprintf(buffer, sizeof(buffer), "%d\xBA", temp);

		// int textWid = screen.getStrWidth(buffer.c_str());
		uint16_t textWid = screen.getStrWidth(buffer);
		screen.setCursor(pxWidth - textWid - padFilX, pxHeight - padFilY);
		screen.print(buffer);
	}

	void drawRealtimeHumidity(uint8_t hum) {
		screen.setDrawColor(2);
		screen.setFont(realtimeFont);
		screen.setFontPosCenter();

		// String text = String(hum, 10);
		// text		= String(text + "%");

		char buffer[5];	   // Space for "100%\0"
		snprintf(buffer, sizeof(buffer), "%d%%", hum);

		screen.setCursor(padRealtimeX, posRealtimeY);

		screen.print(buffer);
	}

	void drawRealtimeTemp(uint8_t temp) {
		screen.setDrawColor(2);
		screen.setFont(realtimeFont);
		screen.setFontPosCenter();

		// String text = String(temp, 10);
		// text		= String(text + "\xBA");

		// int textWid = screen.getStrWidth(text.c_str());

		char buffer[5];	   // Space for "100°\0"
		snprintf(buffer, sizeof(buffer), "%d\xBA", temp);

		uint16_t textWid = screen.getStrWidth(buffer);
		screen.setCursor(pxWidth - textWid - padRealtimeX, posRealtimeY);

		screen.print(buffer);
	}

	void drawAreaBorders() {
		screen.setDrawColor(1);
		// draw top area
		screen.drawFrame(areaTop.x * 8, areaTop.y * 8, areaTop.w * 8, areaTop.h * 8);
		// draw bottom area
		screen.drawFrame(
			areaBottom.x * 8 + 0,
			areaBottom.y * 8 + 0,
			areaBottom.w * 8 + 0,
			areaBottom.h * 8 + 0
		);
		// draw temp area
		screen.drawFrame(areaTemp.x * 8, areaTemp.y * 8, areaTemp.w * 8, areaTemp.h * 8);
		// draw humidity area
		screen.drawFrame(
			areaHumidity.x * 8,
			areaHumidity.y * 8,
			areaHumidity.w * 8,
			areaHumidity.h * 8
		);
	}

	// Dirty functions.
	byte dirties = 0;

	void setDirty(Dirty dirty) {
		bitSet(dirties, static_cast<uint8_t>(dirty));
	}

	void clearDirty(Dirty dirty) {
		bitClear(dirties, static_cast<uint8_t>(dirty));
	}

	bool getDirty(Dirty dirty) {
		return bitRead(dirties, static_cast<uint8_t>(dirty));
	}

	bool checkDirty(Dirty dirty) {
		if (getDirty(dirty)) {
			clearDirty(dirty);
			return true;
		}
		return false;
	}

	void clearDirties() {
		dirties = 0;
	}

}
