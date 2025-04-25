#ifndef SYSTEM_H
#define SYSTEM_H

#include "filaments.h"
#include "thermistor.h"
#include <Arduino.h>
#include <stdint.h>

namespace Sys {
	// Status bits.
	constexpr uint8_t STATUS_OK			 = 0;
	constexpr uint8_t STATUS_ERROR		 = 1;
	constexpr uint8_t STATUS_AWAKE		 = 2;
	constexpr uint8_t STATUS_HEATING	 = 3;
	constexpr uint8_t STATUS_FANNING	 = 4;
	constexpr uint8_t STATUS_BUTTON_DOWN = 5;
	constexpr uint8_t STATUS_SELECT		 = 6;
	constexpr uint8_t STATUS_ACTIVE		 = 7;
	extern byte statuses		;

	// Command bits.
	constexpr uint8_t COMMAND_WAKEUP			  = 0;
	constexpr uint8_t COMMAND_HEATER_ON			  = 1;
	constexpr uint8_t COMMAND_HEATER_OFF		  = 2;
	constexpr uint8_t COMMAND_FAN_ON			  = 3;
	constexpr uint8_t COMMAND_FAN_OFF			  = 4;
	constexpr uint8_t COMMAND_BUTTON_CLICKED	  = 5;
	constexpr uint8_t COMMAND_BUTTON_HELD		  = 6;
	constexpr uint8_t COMMAND_BUTTON_HOLD_HANDLED = 7;
	extern byte commands							;

	/// Dirty bits.
	constexpr uint8_t DIRTY_ALL		 = 0;
	constexpr uint8_t DIRTY_FILAMENT = 1;
	constexpr uint8_t DIRTY_TEMP	 = 2;
	constexpr uint8_t DIRTY_HUMIDITY = 3;
	extern byte dirties				;

	// Timers.
	constexpr uint8_t TIMER_INPUT_POLLING_ACTIVE = 0;
	constexpr uint8_t TIMER_INPUT_POLLING_IDLE	 = 1;
	constexpr uint8_t TIMER_SCREEN_TIMEOUT		 = 2;
	constexpr uint8_t TIMER_HEATER_TIMEOUT		 = 3;
	constexpr uint8_t TIMER_HEATER_COOLDOWN		 = 4;
	constexpr uint8_t TIMER_SELECTION_TIMEOUT	 = 5;
	constexpr uint8_t TIMER_BUTTON_HOLD			 = 6;
	extern uint32_t timers[7];
	extern uint32_t timerIntervals[7];

	// Global time.
	extern uint32_t currentTime;

	// Exhaust temperature delta.
	extern const uint8_t tempDelta;

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

	// Timers.
	extern void setupTimers();

};

#endif
