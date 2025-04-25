#ifndef HTSENSOR_H
#define HTSENSOR_H

#include <Adafruit_SHT31.h>

namespace HtSensor {

	extern Adafruit_SHT31 sensor;
	void setupSensor();
}

#endif
