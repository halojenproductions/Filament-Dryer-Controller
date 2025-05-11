#include "system.h"
#include "utilities.h"
#include <Arduino.h>
#include <unity.h>

#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H

constexpr byte mask = 0b11111111;

namespace suite_util_statuses {
	void suite_Statuses();
}

namespace suite_util_commands {
	void suite_commands();
}

namespace suite_util_errors {
	void suite_Errors();
}

namespace suite_util_timers {
	void suite_Timers();
}

namespace suite_Humidity {
	void suite_Humidity();
}

namespace suite_Temperature {
	void suite_Temperature();
}

void setUp(void);
void tearDown(void);

void setup();

void loop();

#endif
