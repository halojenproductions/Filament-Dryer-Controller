#include "ui.h"
#include <Arduino.h>
#include <unity.h>

using namespace UI;

void setUp(void) {
	// set stuff up here
}

void tearDown(void) {
	// clean stuff up here
}


void test_Therm_Conversion0(void) {
}


void setup() {
	// NOTE!!! Wait for >2 secs
	// if board doesn't support software reset via Serial.DTR/RTS
	delay(200);
	UNITY_BEGIN();

	RUN_TEST(test_Therm_Conversion0);

	UNITY_END();
}

void loop() {}
