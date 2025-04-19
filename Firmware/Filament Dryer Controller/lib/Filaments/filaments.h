#include <WString.h>

#ifndef FILAMENTS_H
#define FILAMENTS_H

struct Filament {
	String name;
	int temperature;
	int humidity;
};

namespace Filaments {
	extern const Filament filaments[];
}

#endif
