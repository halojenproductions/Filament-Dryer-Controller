#include "ht.h"

namespace HT {
	Ops& ops			 = Ops::getInstance();
	Filaments& filaments = Filaments::getInstance();

	Adafruit_SHT31 sensor = Adafruit_SHT31();

	bool readHumid() {
		float humidity = sensor.readHumidity();
		// TODO
		return false;
	}

	bool readTemp() {
		float temperature = sensor.readTemperature();
		// TODO
		return false;
	}

}
