#include "thermistor.h"
#include <math.h>


namespace Thermistor {
	int8_t adcToCelsius(int adc_value) {
		// Convert analog reading to temperature in centigrade
		// Using standard Arduino ADC (10-bit)
		constexpr float K_C		= 273.15;	   // Conversion from Kelvin to Celsius
		constexpr float ADC_MAX = 1023.0;	   // 10-bit ADC max value
		constexpr float R2		= 100000.0;	   // 100kΩ pulldown resistor
		constexpr float BETA	= 3950.0;	   // Beta value from thermistor datasheet
		constexpr float T0		= 50 + K_C;	   // Reference temp in Kelvin (50°C)
		constexpr float R0		= 35840.0;	   // Resistance at 50°C (35.8kΩ from your data)

		// Convert ADC reading to resistance using voltage divider formula
		float r_thermistor = R2 * (ADC_MAX / float(adc_value) - 1.0);

		// Use B-parameter equation with 50°C reference point
		float temp_k = 1.0 / (1.0 / T0 + (1.0 / BETA) * log(r_thermistor / R0));

		// Convert Kelvin to Celsius
		return static_cast<int8_t>(temp_k - K_C);
	}
}
