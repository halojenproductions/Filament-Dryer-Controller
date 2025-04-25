#ifndef FILAMENTS_H
#define FILAMENTS_H

#include "storage.h"
#include <Arduino.h>
#include <WString.h>
#include <avr/pgmspace.h>
#include <stdint.h>

namespace Filaments {
	struct FilamentDef {
		const char* name;
		byte temperature;
		byte humidity;
	};

	extern void apply();
	extern void cancel();
	extern void next();
	extern void retrieve();

	extern FilamentDef activeFilament;
	extern FilamentDef displayFilament;

	extern uint8_t activeIndex;
	extern uint8_t displayIndex;
};
#endif
