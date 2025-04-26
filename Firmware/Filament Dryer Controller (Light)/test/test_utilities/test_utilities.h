#include "system.h"
#include "utilities.h"
#include <Arduino.h>
#include <unity.h>

#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H

namespace suite_Timers {
	void suite_Timers();
}

namespace suite_Humidity {
	void suite_Humidity();
}

namespace suite_Temperature {
	void suite_Temperature();
}

extern void setUp(void);
extern void tearDown(void);

#endif
