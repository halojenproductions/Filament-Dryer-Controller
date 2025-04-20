#include "filaments.h"

Filaments::Filaments() {
	addFilament("PLA", 40, 40);
	addFilament("PETG/TPU", 50, 35);
	addFilament("PC", 80, 30);
}

FilamentDef Filaments::getActive() {
	return Filaments::filaments[activeIndex];
}

FilamentDef Filaments::getDisplay() {
	return Filaments::filaments[displayIndex];
}

void Filaments::apply() {
	activeIndex = displayIndex;
}

void Filaments::cancel() {
	displayIndex = activeIndex;
}

void Filaments::next() {
	displayIndex = (displayIndex + 1) % filamentCount;
}

void Filaments::addFilament(String name, byte temperature, byte humidity) {
	if (filamentCount < maxFilaments) {
		filaments[filamentCount] = {name, temperature, humidity};
		filamentCount++;
	}
}
