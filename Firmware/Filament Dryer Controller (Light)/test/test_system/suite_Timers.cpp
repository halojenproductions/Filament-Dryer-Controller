#include "test_system.h"

using namespace test_Operations_Helpers;

namespace suite_Timers {

	void test_Timers_Unique();
	void test_Timer_Indexes();

	void suite_Timers() {
		RUN_TEST(test_Timers_Unique);
		RUN_TEST(test_Timer_Indexes);
	}

	// Tests.
	void test_Timers_Unique(void) {
		// Create array of all command values
		const uint8_t timerIndexes[] = {
			Sys::TIMER_INPUT_POLLING_ACTIVE,
			Sys::TIMER_INPUT_POLLING_IDLE,
			Sys::TIMER_SCREEN_TIMEOUT,
			Sys::TIMER_HEATER_TIMEOUT,
			Sys::TIMER_HEATER_COOLDOWN,
			Sys::TIMER_SELECTION_TIMEOUT,
			Sys::TIMER_BUTTON_HOLD
		};
		const uint8_t numTimers = sizeof(Sys::timers) / sizeof(Sys::timers[0]);

		assertArrayValuesUnique(timerIndexes, numTimers, "Timer indexes not unique");
	}

	void test_Timer_Indexes(void) {
		TEST_ASSERT_EQUAL(0, Sys::TIMER_INPUT_POLLING_ACTIVE);
		TEST_ASSERT_EQUAL(1, Sys::TIMER_INPUT_POLLING_IDLE);
		TEST_ASSERT_EQUAL(2, Sys::TIMER_SCREEN_TIMEOUT);
		TEST_ASSERT_EQUAL(3, Sys::TIMER_HEATER_TIMEOUT);
		TEST_ASSERT_EQUAL(4, Sys::TIMER_HEATER_COOLDOWN);
		TEST_ASSERT_EQUAL(5, Sys::TIMER_SELECTION_TIMEOUT);
		TEST_ASSERT_EQUAL(6, Sys::TIMER_BUTTON_HOLD);
	}
}
