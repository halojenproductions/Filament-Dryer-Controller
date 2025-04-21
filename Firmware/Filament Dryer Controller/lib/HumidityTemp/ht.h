#ifndef HT_H
#define HT_H

#include "filaments.h"
#include "operations.h"
#include <Adafruit_SHT31.h>
#include <u8g2lib.h>

namespace HT {
	extern Ops& ops;
	extern Filaments& filaments;

	extern Adafruit_SHT31 sensor;

}

#endif
