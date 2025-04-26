#ifndef UTILITIES_H
#define UTILITIES_H

#include "system.h"

namespace Util {
	bool bitCheck(uint8_t& value, uint8_t bitPos);
	void bitClearAll(uint8_t& value);

	// Timer methods.
	bool checkTimer(uint8_t index);
	bool getTimer(uint8_t index);
	void resetTimer(uint8_t index);

	// Inputs.
	/**
	 * \brief Accepts a humidity reading from the sensor.
	 * Sets operations humidity if diffferent.
	 * \param humidity as %
	 * \return \c true if humidity value changed, \c false otherwise
	 * \note Sets Error status if sensor reading is invalid.
	 */
	bool checkHumidity(float humidity);

	/**
	 * \brief Accepts a temperature reading from the sensor.
	 * Sets operations temperature if diffferent.
	 * \param temperature as °C.
	 * \return \c true if temperature value changed, \c false otherwise
	 * \note Sets Error status if sensor reading is invalid or out of range (0-100°C).
	 */
	bool checkTemperature(float temperature);

	/**
	 * \brief Reads and validates temperature from the NTC thermistor.
	 * Sets operations temperature if diffferent.
	 * \param value as 10bit ADC value.
	 * \return \c true if temperature value changed, \c false otherwise
	 * \note Sets Error status if thermistor reading is invalid or out of range (0-100°C).
	 */
	bool checkTherm(int8_t temperature);

}
#endif
