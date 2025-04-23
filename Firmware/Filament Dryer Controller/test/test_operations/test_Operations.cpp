#include "test_Operations.h"

void setUp(void) {
	// set stuff up here
}

void tearDown(void) {
	// clean stuff up here
}

void setup() {
	// delay(2000);
	UNITY_BEGIN();

	// Run all fixtures.
	test_Statuses::test_Statuses();
	test_Dirties::test_Dirties();
	test_Commands::test_Commands();
	test_Humidity::suite_Humidity();

	UNITY_END();
}

void loop() {}
