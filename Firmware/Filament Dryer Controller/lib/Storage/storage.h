#ifndef STORAGE_H
#define STORAGE_H

#include <Arduino.h>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
#include <EEPROM.h>
#pragma GCC diagnostic pop

class Storage {
	public:

	static Storage& getInstance() {
		static Storage instance;
		return instance;
	}

	void saveFilamentIndex(byte index);
	byte loadFilamentIndex();

	private:

	Storage()					   = default;
	Storage(const Storage&)		   = delete;
	void operator=(const Storage&) = delete;

	static constexpr int ADDR_FILAMENT_INDEX = 0;		// EEPROM address
	static constexpr byte MAGIC_BYTE		 = 0xAA;	// For validation
};

#endif
