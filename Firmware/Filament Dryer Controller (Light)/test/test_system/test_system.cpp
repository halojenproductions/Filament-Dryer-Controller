#include "test_system.h"

void setUp(void) {}

void tearDown(void) {}

void setup() {
	delay(200);
	UNITY_BEGIN();

	// Run all fixtures.
	suite_Statuses::suite_Statuses();
	suite_Commands::suite_Commands();
	suite_Dirties::suite_Dirties();
	suite_Timers::suite_Timers();

	UNITY_END();
}

void loop() {}
