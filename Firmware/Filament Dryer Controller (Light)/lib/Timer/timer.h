#ifndef TIMER_H
#define TIMER_H

#include <Arduino.h>
#include <stdint.h>

class Timer {
	public:

	Timer(uint32_t interval);
	bool check(uint32_t time);
	bool get(uint32_t time);
	void reset(uint32_t time);

	private:

	uint32_t value;
	uint32_t interval;
};

#endif
