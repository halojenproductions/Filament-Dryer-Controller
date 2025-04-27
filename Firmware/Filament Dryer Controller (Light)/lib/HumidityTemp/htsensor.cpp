#include "htsensor.h"

namespace HtSensor {

	Adafruit_SHT31 sensor = Adafruit_SHT31();

	void setupSensor() {
		if (!HtSensor::sensor.begin(0x44)) {
			// TODO Uncomment when sensor is connected.
			// Util::setStatus(Sys:: STATUS_Error);	  // TODO handle error.
		}
	}

}
