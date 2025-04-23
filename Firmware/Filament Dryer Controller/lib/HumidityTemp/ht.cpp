#include "ht.h"

namespace HT {
	Ops& ops			 = Ops::getInstance();
	Filaments& filaments = Filaments::getInstance();

	Adafruit_SHT31 sensor = Adafruit_SHT31();

}
