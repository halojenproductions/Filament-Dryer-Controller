#include "timer.h"
#include <Arduino.h>
#include <unity.h>

void setUp(void) {
	// set stuff up here
}

void tearDown(void) {
	// clean stuff up here
}

void test_Timer_Check(void) {
	Timer sut(100);
	TEST_ASSERT_FALSE(sut.check(millis()));
	delay(110);
	TEST_ASSERT_TRUE(sut.check(millis()));
	delay(10);
	TEST_ASSERT_FALSE(sut.check(millis()));
}

void test_Timer_Reset(void) {
	Timer sut(100);
	TEST_ASSERT_FALSE(sut.check(millis()));
	delay(60);
	sut.reset();
	delay(60);
	TEST_ASSERT_FALSE(sut.check(millis()));
}

void setup() {
	// NOTE!!! Wait for >2 secs
	// if board doesn't support software reset via Serial.DTR/RTS
	// delay(2000);
	UNITY_BEGIN();

	RUN_TEST(test_Timer_Check);
	RUN_TEST(test_Timer_Reset);

	UNITY_END();
}

void loop() {}
