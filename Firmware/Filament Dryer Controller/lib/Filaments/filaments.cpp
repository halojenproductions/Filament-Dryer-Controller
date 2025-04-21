#include "filaments.h"

namespace {
	// Keep filament definitions together in one place
	constexpr byte FILAMENT_COUNT						= 3;
	const FilamentDef FILAMENTS[FILAMENT_COUNT] PROGMEM = {
		{"PLA", 40, 40}, {"PETG/TPU", 50, 35}, {"PC", 80, 30}
	};
}

const FilamentDef& Filaments::getActive() const {
	return activeFilament;
}

const FilamentDef& Filaments::getDisplay() const {
	return displayFilament;
}

void Filaments::apply() {
	activeIndex = displayIndex;
	memcpy_P(&activeFilament, &FILAMENTS[activeIndex], sizeof(FilamentDef));
	Storage::getInstance().saveFilamentIndex(activeIndex);
}

void Filaments::cancel() {
	displayIndex = activeIndex;
	memcpy_P(&displayFilament, &FILAMENTS[displayIndex], sizeof(FilamentDef));
}

void Filaments::next() {
	displayIndex = (displayIndex + 1) % FILAMENT_COUNT;
	memcpy_P(&displayFilament, &FILAMENTS[displayIndex], sizeof(FilamentDef));
}

Filaments::Filaments() {
	activeIndex	 = Storage::getInstance().loadFilamentIndex();
	displayIndex = activeIndex;
	memcpy_P(&activeFilament, &FILAMENTS[activeIndex], sizeof(FilamentDef));
	memcpy_P(&displayFilament, &FILAMENTS[displayIndex], sizeof(FilamentDef));
}
