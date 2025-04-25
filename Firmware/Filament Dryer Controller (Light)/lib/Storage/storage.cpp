#include "storage.h"

void Storage::saveFilamentIndex(byte index) {
	EEPROM.write(ADDR_FILAMENT_INDEX, MAGIC_BYTE);
	EEPROM.write(ADDR_FILAMENT_INDEX + 1, index);
}

byte Storage::loadFilamentIndex() {
	if (EEPROM.read(ADDR_FILAMENT_INDEX) != MAGIC_BYTE) {
		return 0;	 // Default to first filament if no valid data
	}
	return EEPROM.read(ADDR_FILAMENT_INDEX + 1);
}
