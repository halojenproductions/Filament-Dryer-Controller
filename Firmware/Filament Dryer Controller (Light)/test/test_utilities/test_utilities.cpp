#include "test_utilities.h"

void setUp(void) {}

void tearDown(void) {}

void setup() {
	delay(1000);
	UNITY_BEGIN();

	// Run all fixtures.
	suite_Timers::suite_Timers();

	UNITY_END();
}

void loop() {}
