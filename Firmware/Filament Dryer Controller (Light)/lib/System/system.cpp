#include "system.h"

namespace Sys {
	byte statuses			   = 0;
	byte commands			   = 0;
	byte dirties			   = 0;
	uint32_t timers[7]		   = {0};
	uint32_t timerIntervals[7] = {0};

	// Global time.
	uint32_t currentTime		= millis();
	// Exhaust temperature delta.
	constexpr uint8_t tempDelta = 5;	// Degrees Celsius.

	uint8_t sensHumid = 0;
	uint8_t sensTemp  = 99;
	uint8_t thermTemp = 99;

	void setupTimers() {
		timerIntervals[TIMER_INPUT_POLLING_ACTIVE] = 100UL;
		timerIntervals[TIMER_INPUT_POLLING_IDLE]   = 1000UL * 60;
		timerIntervals[TIMER_SCREEN_TIMEOUT]	   = 1000UL * 30;
		timerIntervals[TIMER_HEATER_TIMEOUT]	   = 1000UL * 60 * 2;
		timerIntervals[TIMER_HEATER_COOLDOWN]	   = 1000UL * 60 * 2;
		timerIntervals[TIMER_SELECTION_TIMEOUT]	   = 1000UL * 5;
		timerIntervals[TIMER_BUTTON_HOLD]		   = 800UL;

		timers[TIMER_INPUT_POLLING_ACTIVE] = millis();
		timers[TIMER_INPUT_POLLING_IDLE]   = millis();
		timers[TIMER_SCREEN_TIMEOUT]	   = millis();
		timers[TIMER_HEATER_TIMEOUT]	   = millis();
		timers[TIMER_HEATER_COOLDOWN]	   = millis();
		timers[TIMER_SELECTION_TIMEOUT]	   = millis();
		timers[TIMER_BUTTON_HOLD]		   = millis();
	}

}
