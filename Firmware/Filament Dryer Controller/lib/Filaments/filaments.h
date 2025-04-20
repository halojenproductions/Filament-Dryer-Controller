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

	FilamentDef getActive();
	FilamentDef getDisplay();
	void apply();
	void cancel();
	void next();

	// Singleton stuff.
	static Filaments& getInstance() {
		static Filaments instance;
		return instance;
	}

	Filaments(const Filaments&)		 = delete;
	void operator=(const Filaments&) = delete;

	private:

	// Private constructor
	Filaments();

	void addFilament(String name, byte temperature, byte humidity);

	static const byte maxFilaments = 8;
	FilamentDef filaments[maxFilaments];
	byte filamentCount = 0;
	byte activeIndex   = 0;
	byte displayIndex  = 0;
};

#endif
