#include "thermistor.h"
#include <Arduino.h>
#include <unity.h>

using namespace Thermistor;

void setUp(void) {
	// set stuff up here
}

void tearDown(void) {
	// clean stuff up here
}

const float tolerance = 1.0;	// +/- for temperature conversion

bool withinTolerance(int value, int target, float above, float below) {
	return ((float)value >= (float)target - below && (float)value <= (float)target + above);
}

void test_Therm_Conversion0(void) {
	uint8_t expected = 0;
	int adcValue	 = 242;
	// TEST_ASSERT_LESS_OR_EQUAL_FLOAT((float)expected + 0.428, (float)sut);
	// TEST_ASSERT_GREATER_OR_EQUAL_FLOAT((float)expected - 0.421, (float)sut);
	TEST_ASSERT_FLOAT_WITHIN(tolerance, expected, adcToCelsius(adcValue));
}

void test_Therm_Conversion25(void) {
	uint8_t expected = 25;
	int adcValue	 = 511;
	// TEST_ASSERT_LESS_OR_EQUAL_FLOAT((float)expected + 0.229, (float)sut);
	// TEST_ASSERT_GREATER_OR_EQUAL_FLOAT((float)expected - 0.229, (float)sut);
	TEST_ASSERT_FLOAT_WITHIN(tolerance, expected, adcToCelsius(adcValue));
}

void test_Therm_Conversion50(void) {
	uint8_t expected = 50;
	int adcValue	 = 753;
	// TEST_ASSERT_LESS_OR_EQUAL_FLOAT((float)expected + 0.539, (float)sut);
	// TEST_ASSERT_GREATER_OR_EQUAL_FLOAT((float)expected - 0.530, (float)sut);
	TEST_ASSERT_FLOAT_WITHIN(tolerance, expected, adcToCelsius(adcValue));
}

void test_Therm_Conversion75(void) {
	uint8_t expected = 75;
	int adcValue	 = 893;
	// TEST_ASSERT_LESS_OR_EQUAL_FLOAT((float)expected + 0.975, (float)sut);
	// TEST_ASSERT_GREATER_OR_EQUAL_FLOAT((float)expected - 0.948, (float)sut);
	TEST_ASSERT_FLOAT_WITHIN(tolerance, expected, adcToCelsius(adcValue));
}

void test_Therm_Conversion100(void) {
	uint8_t expected = 100;
	int adcValue	 = 960;
	// TEST_ASSERT_LESS_OR_EQUAL_FLOAT((float)expected + 1.304, (float)sut);
	// TEST_ASSERT_GREATER_OR_EQUAL_FLOAT((float)expected - 1.260, (float)sut);
	TEST_ASSERT_FLOAT_WITHIN(2.0, expected, adcToCelsius(adcValue));
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
