#include "test_utilities.h"

namespace suite_Timers {
	void test_Timers_Setup();
	void test_Timers_GetCheckReset();
	void testTimerSetup(uint8_t index);

	void suite_Timers() {
		RUN_TEST(test_Timers_Setup);
		RUN_TEST(test_Timers_GetCheckReset);
	}

	// Tests.
	void test_Timers_Setup(void) {
		Sys::setupTimers();

		testTimerSetup(Sys::TIMER_INPUT_POLLING_IDLE);
		testTimerSetup(Sys::TIMER_SCREEN_TIMEOUT);
		testTimerSetup(Sys::TIMER_HEATER_TIMEOUT);
		testTimerSetup(Sys::TIMER_HEATER_COOLDOWN);
		testTimerSetup(Sys::TIMER_SELECTION_TIMEOUT);
		testTimerSetup(Sys::TIMER_BUTTON_HOLD);
	}

	void test_Timers_GetCheckReset(void) {
		Sys::timerIntervals[0] = 100UL;
		Sys::timers[0]		   = millis();
		Sys::currentTime	   = millis();

		// Within interval.
		TEST_ASSERT_FALSE(Util::getTimer(0));
		TEST_ASSERT_FALSE(Util::checkTimer(0));

		// Beyond interval.
		delay(110);
		Sys::currentTime = millis();
		TEST_ASSERT_TRUE(Util::getTimer(0));
		TEST_ASSERT_TRUE(Util::checkTimer(0));

		// Was reset when checked beyond interval.
		TEST_ASSERT_FALSE(Util::checkTimer(0));
	}

	void testTimerSetup(uint8_t index) {
		TEST_ASSERT_GREATER_THAN(0, Sys::timerIntervals[index]);
		TEST_ASSERT_GREATER_THAN(0, Sys::timers[index]);
	}
}
