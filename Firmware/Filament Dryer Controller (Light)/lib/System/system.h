#ifndef SYSTEM_H
#define SYSTEM_H

#include "filaments.h"
#include "thermistor.h"
#include "timer.h"
#include <Arduino.h>
#include <stdint.h>

namespace Sys {
	enum class Status : uint16_t {
		Ok,
		Error,
		ScreenAwake,
		Heating,
		HeatDuty,
		ButtonDown,
		Select,
		Active,
		_Last
	};

	extern byte statuses;

	enum class Command : uint8_t {
		WakeUp,
		HandleButtonHold,
		_Last
	};

	extern byte commands;

	enum class Error : uint16_t {
		ActiveTimeout,		// Warning. (Humidity has not decreased. Desiccant saturated? Lid open?)
		HeatingTimeout,		// Pause. (Box has not reached temperature. Lid open?)
		HeatDutyTimeout,	// Terminal. (Heater broken? Thermistor broken?)
		Sensor,				// Terminal. (Humidity/temperature out of range. Sensor broken?)
		Thermistor,			// Terminal. (Therm out of range. Thermistor broken?)
		_Last
	};

	extern byte errors;

	// Timers.
	constexpr uint32_t INPUT_POLL_ACTIVE_INTERVAL	  = 200;
	constexpr uint32_t INPUT_POLL_IDLE_INTERVAL		  = 1000UL * 60;
	constexpr uint32_t SCREEN_TIMEOUT_INTERVAL		  = 1000UL * 300;	 // TODO: Change back to 30.
	constexpr uint32_t ACTIVE_TIMEOUT_INTERVAL		  = 1000UL * 60 * 5;
	constexpr uint32_t ACTIVE_COOLDOWN_INTERVAL		  = 1000UL * 60 * 2;
	constexpr uint32_t HEATING_TIMEOUT_INTERVAL		  = 1000UL * 60 * 2;
	constexpr uint32_t HEATING_COOLDOWN_TIME_INTERVAL = 1000UL * 60 * 20;
	constexpr uint32_t HEAT_DUTY_TIMEOUT_INTERVAL	  = 1000UL * 4;
	constexpr uint32_t SELECTION_TIMEOUT_INTERVAL	  = 1000UL * 5;
	constexpr uint32_t BUTTON_HOLD_TIMEOUT_INTERVAL	  = 800;

	extern Timer activeInputPolling;
	extern Timer idleInputPolling;
	extern Timer screenTimeout;
	extern Timer selectionTimeout;
	extern Timer buttonHoldTimeout;

	// Global time.
	extern uint32_t currentTime;

	// Exhaust temperature delta.
	extern const uint8_t tempDelta;

	// Fan speeds.
	extern const uint8_t FAN_SPEED_LOW;
	extern const uint8_t FAN_SPEED_HIGH;

	// Inputs.
	/**
	 * \brief Gets the current humidity reading from the sensor
	 * \return Humidity as percentage (0-100)
	 * \note Returns 0 if no valid reading has been received
	 */
	extern uint8_t sensHumid;

	/**
	 * \brief Gets the current temperature reading from the SHT31 sensor
	 * \return Temperature in Celsius
	 * \note Returns 99 if no valid reading has been received
	 */
	extern uint8_t sensTemp;

	/**
	 * \brief Gets the current temperature reading from the NTC thermistor
	 * \return Temperature in Celsius
	 * \note Returns 99 if no valid reading has been received
	 */
	extern uint8_t thermTemp;

};

#endif
