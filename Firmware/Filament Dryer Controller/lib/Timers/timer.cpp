#include "timer.h"

Timer::Timer(uint32_t intervalMillis) {
	value	 = millis();
	interval = intervalMillis;
}

bool Timer::check(uint32_t presentTime) {
	if (presentTime >= value + interval) {
		value = presentTime;
		return true;
	}
	return false;
}
