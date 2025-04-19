#include "filaments.h"

const FilamentDef Filaments::filaments[] = {{"PLA", 40, 40}, {"PETG/TPU", 50, 35}, {"PC", 80, 30}};

void Filaments::apply() {
	activeIndex						  = displayIndex;
	const_cast<FilamentDef &>(active) = filaments[activeIndex];	   // Update active reference
}

void Filaments::cancel() {
	displayIndex					   = activeIndex;
	const_cast<FilamentDef &>(display) = filaments[displayIndex];	 // Update display reference
}

void Filaments::next() {
	displayIndex = (displayIndex + 1) % (sizeof(filaments) / sizeof(filaments[0]));
	const_cast<FilamentDef &>(display) = filaments[displayIndex];	 // Update reference
}
