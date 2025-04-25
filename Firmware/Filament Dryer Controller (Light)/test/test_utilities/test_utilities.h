#include "system.h"
#include "utilities.h"
#include <Arduino.h>
#include <unity.h>

#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H

namespace suite_Timers {
	void suite_Timers();
}

extern void setUp(void);
extern void tearDown(void);

#endif
