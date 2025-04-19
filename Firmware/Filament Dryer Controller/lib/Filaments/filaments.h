#include <Arduino.h>
#include <WString.h>
#include <stdint.h>

#ifndef FILAMENTS_H
#define FILAMENTS_H

struct FilamentDef {
	String name;
	byte temperature;
	byte humidity;
};

class Filaments {
	public:

	static Filaments &getInstance() {
		static Filaments instance;
		return instance;
	}

	// Delete copy constructor and assignment operator
	Filaments(const Filaments &)	  = delete;
	void operator=(const Filaments &) = delete;

	const FilamentDef &active;
	const FilamentDef &display;

	void apply();
	void cancel();
	void next();

	private:

	// Private constructor
	Filaments() : active(filaments[0]), display(filaments[0]) {}

	static const FilamentDef filaments[];
	byte activeIndex  = 0;
	byte displayIndex = 0;
};

#endif
