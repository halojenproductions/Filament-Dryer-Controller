#ifndef UTILITIES_H
#define UTILITIES_H

#include "Arduino.h"
#include "system.h"

namespace Util {

	// Timer methods.
	bool checkTimer(Timer& timer);
	bool getTimer(Timer& timer);
	void resetTimer(Timer& timer);

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

	// Status methods.
	void setStatus(Sys::Status status);
	void clearStatus(Sys::Status status);
	void toggleStatus(Sys::Status status);
	bool getStatus(Sys::Status status);

	// Command methods.
	void setCommand(Sys::Command command);
	void clearCommand(Sys::Command command);
	bool getCommand(Sys::Command command);
	bool checkCommand(Sys::Command command);

}
#endif
