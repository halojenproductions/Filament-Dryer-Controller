#include "timer.h"

Timer::Timer(uint32_t intervalMillis) {
	value	 = millis();
	interval = intervalMillis;
}

bool Timer::check(uint32_t time) {
	if (get(time)) {
		reset(time);
		return true;
	}
	return false;
}

bool Timer::get(uint32_t time) {
	return (time >= value + interval);
}

void Timer::reset(uint32_t time) {
	value = time;
}
