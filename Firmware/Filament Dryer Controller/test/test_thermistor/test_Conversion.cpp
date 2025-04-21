#include "thermistor.h"
#include <Arduino.h>
#include <unity.h>

void setUp(void) {
	// set stuff up here
}

void tearDown(void) {
	// clean stuff up here
}

bool withinTolerance(int value, int target, float above, float below) {
	return ((float)value >= (float)target - below && (float)value <= (float)target + above);
}

const float tolerance = 1.0;	// +/- for temperature conversion

void test_Therm_Conversion0(void) {
	int expected = 0;
	Thermistor sut;
	sut = 242;
	// TEST_ASSERT_LESS_OR_EQUAL_FLOAT((float)expected + 0.428, (float)sut);
	// TEST_ASSERT_GREATER_OR_EQUAL_FLOAT((float)expected - 0.421, (float)sut);
	TEST_ASSERT_FLOAT_WITHIN(tolerance, expected, sut);
}

void test_Therm_Conversion25(void) {
	int expected   = 25;
	Thermistor sut = 511;
	// TEST_ASSERT_LESS_OR_EQUAL_FLOAT((float)expected + 0.229, (float)sut);
	// TEST_ASSERT_GREATER_OR_EQUAL_FLOAT((float)expected - 0.229, (float)sut);
	TEST_ASSERT_FLOAT_WITHIN(tolerance, expected, sut);
}

void test_Therm_Conversion50(void) {
	int expected   = 50;
	Thermistor sut = 753;
	// TEST_ASSERT_LESS_OR_EQUAL_FLOAT((float)expected + 0.539, (float)sut);
	// TEST_ASSERT_GREATER_OR_EQUAL_FLOAT((float)expected - 0.530, (float)sut);
	TEST_ASSERT_FLOAT_WITHIN(tolerance, expected, sut);
}

void test_Therm_Conversion75(void) {
	int expected   = 75;
	Thermistor sut = 893;
	// TEST_ASSERT_LESS_OR_EQUAL_FLOAT((float)expected + 0.975, (float)sut);
	// TEST_ASSERT_GREATER_OR_EQUAL_FLOAT((float)expected - 0.948, (float)sut);
	TEST_ASSERT_FLOAT_WITHIN(tolerance, expected, sut);
}

void test_Therm_Conversion100(void) {
	int expected   = 100;
	Thermistor sut = 960;
	// TEST_ASSERT_LESS_OR_EQUAL_FLOAT((float)expected + 1.304, (float)sut);
	// TEST_ASSERT_GREATER_OR_EQUAL_FLOAT((float)expected - 1.260, (float)sut);
	TEST_ASSERT_FLOAT_WITHIN(2.0, expected, sut);
}

void setup() {
	// NOTE!!! Wait for >2 secs
	// if board doesn't support software reset via Serial.DTR/RTS
	// delay(2000);
	UNITY_BEGIN();

	RUN_TEST(test_Therm_Conversion0);
	RUN_TEST(test_Therm_Conversion25);
	RUN_TEST(test_Therm_Conversion50);
	RUN_TEST(test_Therm_Conversion75);
	RUN_TEST(test_Therm_Conversion100);

	UNITY_END();
}

void loop() {}
