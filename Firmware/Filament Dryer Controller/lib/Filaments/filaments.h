#ifndef FILAMENTS_H
#define FILAMENTS_H

#include <Arduino.h>
#include <WString.h>
#include <avr/pgmspace.h>
#include <stdint.h>

struct FilamentDef {
	const char* name;
	byte temperature;
	byte humidity;
};

class Filaments {
	public:

	static Filaments& getInstance() {
		static Filaments instance;
		return instance;
	}

	const FilamentDef& getActive() const;
	const FilamentDef& getDisplay() const;
	void apply();
	void cancel();
	void next();

	private:

	Filaments();
	Filaments(const Filaments&)		 = delete;
	void operator=(const Filaments&) = delete;

	static const PROGMEM FilamentDef filamentData[];
	FilamentDef activeFilament;
	FilamentDef displayFilament;

	byte activeIndex  = 0;
	byte displayIndex = 0;
};
#endif
