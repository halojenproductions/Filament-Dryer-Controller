#include "test_utilities.h"

namespace suite_Timers {

	void test_Timers_Setup();
	void test_Timers_Check();

	void suite_Timers() {
		RUN_TEST(test_Timers_Setup);
		RUN_TEST(test_Timers_Check);
	}

	// Tests.
	void test_Timers_Setup(void) {
		Sys::setupTimers();
		// TODO
	}

	void test_Timers_Check(void) {
		Sys::timerIntervals[0] = 100UL;
		Sys::timers[0]		   = millis();
		Sys::currentTime	   = millis();

		TEST_ASSERT_FALSE(Util::checkTimer(0));
		delay(110);
		Sys::currentTime = millis();
		TEST_ASSERT_TRUE(Util::checkTimer(0));
		delay(10);
		Sys::currentTime = millis();
		TEST_ASSERT_FALSE(Util::checkTimer(0));
	}
}
