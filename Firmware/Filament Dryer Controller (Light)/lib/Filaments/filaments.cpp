#include "filaments.h"

namespace Filaments {

	// Keep filament definitions together in one place
	constexpr uint8_t FILAMENT_COUNT					= 8;
	const FilamentDef FILAMENTS[FILAMENT_COUNT] PROGMEM = {
		{"PVA", 30, 40},
		{"PLA", 40, 40},
		{"TPU/TPE", 45, 30},
		{"PETG", 55, 30},
		{"ABS/ASA", 60, 35},
		{"HIPS", 65, 25},
		{"PC", 65, 20},
		{"PA", 70, 15}
	};

	FilamentDef activeFilament;
	FilamentDef displayFilament;

	uint8_t activeIndex	 = 0;
	uint8_t displayIndex = 0;

	void apply() {
		activeIndex = displayIndex;
		memcpy_P(&activeFilament, &FILAMENTS[activeIndex], sizeof(FilamentDef));
		Storage::getInstance().saveFilamentIndex(activeIndex);
	}

	void cancel() {
		displayIndex = activeIndex;
		memcpy_P(&displayFilament, &FILAMENTS[displayIndex], sizeof(FilamentDef));
	}

	void next() {
		displayIndex = (displayIndex + 1) % FILAMENT_COUNT;
		memcpy_P(&displayFilament, &FILAMENTS[displayIndex], sizeof(FilamentDef));
	}

	void retrieve() {
		activeIndex	 = Storage::getInstance().loadFilamentIndex();
		displayIndex = activeIndex;
		memcpy_P(&activeFilament, &FILAMENTS[activeIndex], sizeof(FilamentDef));
		memcpy_P(&displayFilament, &FILAMENTS[displayIndex], sizeof(FilamentDef));
	}

}
