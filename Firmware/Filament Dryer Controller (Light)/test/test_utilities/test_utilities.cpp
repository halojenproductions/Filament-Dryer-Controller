#include "test_utilities.h"

void setUp(void) {}

void tearDown(void) {}

void setup() {
	delay(200);
	UNITY_BEGIN();

	// Run all fixtures.
	suite_Timers::suite_Timers();
	suite_Humidity::suite_Humidity();
	suite_Temperature::suite_Temperature();

	UNITY_END();
}

void loop() {}
