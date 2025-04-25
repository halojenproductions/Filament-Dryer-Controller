#include "test_system.h"

using namespace test_Operations_Helpers;

namespace suite_Timers {

	void test_Timer_INPUT_POLLING_ACTIVE();
	void test_Timer_INPUT_POLLING_IDLE();
	void test_Timer_SCREEN_TIMEOUT();
	void test_Timer_HEATER_TIMEOUT();
	void test_Timer_HEATER_COOLDOWN();
	void test_Timer_SELECTION_TIMEOUT();
	void test_Timer_BUTTON_HOLD();
	void testSingleTimer(uint8_t bitPos, uint8_t status);

	void suite_Timers() {
		RUN_TEST(test_Timer_INPUT_POLLING_ACTIVE);
		RUN_TEST(test_Timer_INPUT_POLLING_IDLE);
		RUN_TEST(test_Timer_SCREEN_TIMEOUT);
		RUN_TEST(test_Timer_HEATER_TIMEOUT);
		RUN_TEST(test_Timer_HEATER_COOLDOWN);
		RUN_TEST(test_Timer_SELECTION_TIMEOUT);
		RUN_TEST(test_Timer_BUTTON_HOLD);
	}

	// Tests.
	void test_Timer_INPUT_POLLING_ACTIVE(void) {
		testSingleTimer(0, Sys::TIMER_INPUT_POLLING_ACTIVE);
	}

	void test_Timer_INPUT_POLLING_IDLE(void) {
		testSingleTimer(1, Sys::TIMER_INPUT_POLLING_IDLE);
	}

	void test_Timer_SCREEN_TIMEOUT(void) {
		testSingleTimer(2, Sys::TIMER_SCREEN_TIMEOUT);
	}

	void test_Status_HEATING(void) {
		testSingleTimer(3, Sys::TIMER_HEATER_TIMEOUT);
	}

	void test_Status_FANNING(void) {
		testSingleTimer(4, Sys::TIMER_HEATER_COOLDOWN);
	}

	void test_Status_BUTTON_DOWN(void) {
		testSingleTimer(5, Sys::TIMER_SELECTION_TIMEOUT);
	}

	void test_Status_SELECT(void) {
		testSingleTimer(6, Sys::TIMER_BUTTON_HOLD);
	}

	void testSingleTimer(uint8_t bitPos, uint8_t status) {
		Sys::statuses = 0;	  // Reset statuses to 0

		uint8_t expected = (1 << bitPos);

		// Set.
		bitSet(Sys::statuses, status);
		TEST_ASSERT_BITS(mask, expected, Sys::statuses);
		// Get.
		TEST_ASSERT_TRUE(bitRead(Sys::statuses, status));
		// Clear.
		bitClear(Sys::statuses, status);
		TEST_ASSERT_BITS_LOW(mask, Sys::statuses);
		// Check.
		bitSet(Sys::statuses, status);
		TEST_ASSERT_TRUE(Util::bitCheck(Sys::statuses, status));
		TEST_ASSERT_FALSE(Util::bitCheck(Sys::statuses, status));
		TEST_ASSERT_BITS_LOW(mask, Sys::statuses);
	}
}
