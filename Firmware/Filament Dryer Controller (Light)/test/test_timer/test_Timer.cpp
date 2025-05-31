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

void test_Timer_MillisOverflow(void) {
	Timer sut(100UL);
	uint32_t currentTime = 0UL - 10;	// 10 ms before overflow.
	sut.reset(currentTime);

	// Simulate millis overflow 10ms after overflow.
	currentTime = 0UL + 10;

	// Within interval.
	TEST_ASSERT_FALSE(sut.get(currentTime));

	// Beyond interval.
	currentTime += 100;
	TEST_ASSERT_TRUE(sut.get(currentTime));
}

void setup() {
	// NOTE!!! Wait for >2 secs
	// if board doesn't support software reset via Serial.DTR/RTS
	delay(200);
	UNITY_BEGIN();

	RUN_TEST(test_Timer_Check);
	RUN_TEST(test_Timer_MillisOverflow);

	UNITY_END();
}

void loop() {}
