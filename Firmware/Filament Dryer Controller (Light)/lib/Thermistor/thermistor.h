#ifndef THERMISTOR_H
#define THERMISTOR_H

#include <stdint.h>

namespace Thermistor {

	/**
	 * \brief Converts thermistor ADC value to Celsius.
	 * \param adc_value ADC value (0-1023).
	 * \return Temperature in Celsius.
	 *
	 * \warning The thermistor is connected to the positive rail a 100kΩ external pull-down
	 * resistor.
	 *
	 * \details Takes the ADC value from a 100kΩ thermistor connected to an analogue pin,
	 * with a 100kΩ pulldown resistor, and converts it to Celsius.
	 *
	 * \note The thermistor is NTC, 100kΩ@25°C, B-value 3950K.
	 * \note Uses the B-value equation with a reference temperature of 50°C.
	 * \note Thermistor Beta value = 3950
	 *
	 * \note https://www.ametherm.com/thermistor/ntc-thermistor-beta
	 * \note Temperature, resistance, ADC. Derived from a datasheet.
	 * \note -25° = 1265.000kΩ = 74
	 * \note 0° = 328.157kΩ = 242
	 * \note 25° = 100kΩ = 511
	 * \note 50° = 35.840kΩ = 753
	 * \note 75° = 14.517kΩ = 893
	 * \note 100° = 6.498kΩ = 960
	 * \note 125° = 3.186kΩ = 990
	 */
	extern int8_t adcToCelsius(int adc_value);
}

#endif
