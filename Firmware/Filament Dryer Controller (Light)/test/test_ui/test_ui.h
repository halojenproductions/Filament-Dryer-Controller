#include "system.h"
#include "ui.h"
#include "utilities.h"
#include <Arduino.h>
#include <unity.h>

#ifndef TEST_UI_H
#define TEST_UI_H

namespace test_ui_dirties {
	void suite_Dirties();
}

void setUp(void) {}

void tearDown(void) {}

void setup() {
	delay(200);
	UNITY_BEGIN();

	// Run all fixtures.
	test_ui_dirties::suite_Dirties();

	UNITY_END();
}

void loop() {}

#endif
