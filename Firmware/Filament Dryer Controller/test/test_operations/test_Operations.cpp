#include "test_Operations.h"

void setUp(void) {}

void tearDown(void) {}

void setup() {
	// delay(2000);
	UNITY_BEGIN();

	// Run all fixtures.
	suite_Statuses::suite_Statuses();
	suite_Dirties::suite_Dirties();
	suite_Commands::suite_Commands();
	suite_Humidity::suite_Humidity();

	UNITY_END();
}

void loop() {}
