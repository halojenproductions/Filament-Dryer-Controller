#include "temperature.h"
#include <math.h>

/*
	NTC Thermistors Beta value = 3950
	https://www.ametherm.com/thermistor/ntc-thermistor-beta
	0° = 321kΩ = 243
	25° = 100kΩ = 511
	50° = 35k8Ω = 753
	80° = 12k3Ω = 911
	100° = 6k5Ω = 961
*/

OutTemp::OutTemp(int value) : temp_(value) {}

// Implicit conversion from centigrade to analogue value.
OutTemp::operator int() const {
	return temp_;
}

// Implicit conversion from analogue value to centigrade.
OutTemp &OutTemp::operator=(int value) {
	// TODO: Convert analog reading to temperature in centigrade
	// Using standard Arduino ADC (10-bit), voltage reference, and NTC thermistor calculations
	temp_ = adcToCelsius(value);
	return *this;
}

int temp_;

int OutTemp::adcToCelsius(int adc_value) {
	const float BETA	  = 3950.0;	   // Beta value from thermistor datasheet
	const float T0		  = 298.15;	   // Room temp in Kelvin (25°C)
	const float ADC_AT_T0 = 511.0;	   // ADC reading at 25°C

	// Calculate temperature using Beta equation
	float temp_k = 1.0 / (1.0 / T0 + (1.0 / BETA) * log(adc_value / ADC_AT_T0));

	// Convert Kelvin to Celsius
	return static_cast<int>(temp_k - 273.15);
}
