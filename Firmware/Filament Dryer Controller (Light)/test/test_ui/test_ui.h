#include "system.h"
#include "ui.h"
#include "utilities.h"
#include <Arduino.h>
#include <unity.h>

#ifndef TEST_UTILITIES_H
#define TEST_UTILITIES_H

namespace test_Ui_Dirties {
	void suite_Ui_Dirties();
}

void setUp(void) {}

void tearDown(void) {}

void setup() {
	delay(200);
	UNITY_BEGIN();

	// Run all fixtures.
	test_Ui_Dirties::suite_Ui_Dirties();

	UNITY_END();
}

void loop() {}

#endif
