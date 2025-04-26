#ifndef SYSTEM_H
#define SYSTEM_H

#include "filaments.h"
#include "thermistor.h"
#include "timer.h"
#include <Arduino.h>
#include <stdint.h>

namespace Sys {
	// Status bits.
	constexpr uint8_t STATUS_OK			 = 0;
	constexpr uint8_t STATUS_ERROR		 = 1;
	constexpr uint8_t STATUS_AWAKE		 = 2;
	constexpr uint8_t STATUS_HEATING	 = 3;
	constexpr uint8_t STATUS_HEAT_DUTY	 = 4;
	constexpr uint8_t STATUS_BUTTON_DOWN = 5;
	constexpr uint8_t STATUS_SELECT		 = 6;
	constexpr uint8_t STATUS_ACTIVE		 = 7;
	extern byte statuses;

	// Command bits.
	constexpr uint8_t COMMAND_WAKEUP			  = 0;
	constexpr uint8_t COMMAND_HEATER_ON			  = 1;
	constexpr uint8_t COMMAND_HEATER_OFF		  = 2;
	constexpr uint8_t COMMAND_FAN_ON			  = 3;
	constexpr uint8_t COMMAND_FAN_OFF			  = 4;
	constexpr uint8_t COMMAND_BUTTON_CLICKED	  = 5;
	constexpr uint8_t COMMAND_BUTTON_HELD		  = 6;
	constexpr uint8_t COMMAND_BUTTON_HOLD_HANDLED = 7;
	extern byte commands;

	/// Dirty bits.
	constexpr uint8_t DIRTY_ALL		 = 0;
	constexpr uint8_t DIRTY_FILAMENT = 1;
	constexpr uint8_t DIRTY_TEMP	 = 2;
	constexpr uint8_t DIRTY_HUMIDITY = 3;
	extern byte dirties;

	// Timers.
	constexpr uint32_t INPUT_POLL_ACTIVE_INTERVAL	  = 200;
	constexpr uint32_t INPUT_POLL_IDLE_INTERVAL		  = 1000UL * 60;
	constexpr uint32_t SCREEN_TIMEOUT_INTERVAL		  = 1000UL * 30;
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
