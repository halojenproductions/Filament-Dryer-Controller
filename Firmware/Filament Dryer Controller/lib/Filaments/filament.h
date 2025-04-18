#include <WString.h>

#ifndef FILAMENT_H
#define FILAMENT_H

struct Filament {
	String name;
	int temperature;
	int humidity;
};

namespace Filaments {
	extern const Filament filaments[];
}

#endif
