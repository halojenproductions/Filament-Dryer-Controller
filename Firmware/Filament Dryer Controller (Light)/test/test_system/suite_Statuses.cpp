#include "test_system.h"

using namespace test_Operations_Helpers;

namespace suite_Statuses {

	void test_Status_OK();
	void test_Status_ERROR();
	void test_Status_AWAKE();
	void test_Status_HEATING();
	void test_Status_FANNING();
	void test_Status_BUTTON_DOWN();
	void test_Status_SELECT();
	void test_Status_ACTIVE();
	void testSingleStatus(uint8_t bitPos, uint8_t status);

	void suite_Statuses() {
		RUN_TEST(test_Status_OK);
		RUN_TEST(test_Status_ERROR);
		RUN_TEST(test_Status_AWAKE);
		RUN_TEST(test_Status_HEATING);
		RUN_TEST(test_Status_FANNING);
		RUN_TEST(test_Status_BUTTON_DOWN);
		RUN_TEST(test_Status_SELECT);
		RUN_TEST(test_Status_ACTIVE);
	}

	// Tests.
	void test_Statuses_Unique() {
		// Create array of all command values
		const uint8_t statusBitPositions[] = {
			Sys::STATUS_OK,
			Sys::STATUS_ERROR,
			Sys::STATUS_AWAKE,
			Sys::STATUS_HEATING,
			Sys::STATUS_FANNING,
			Sys::STATUS_BUTTON_DOWN,
			Sys::STATUS_SELECT,
			Sys::STATUS_ACTIVE
		};
		const uint8_t numStatuses = sizeof(statusBitPositions) / sizeof(statusBitPositions[0]);

		// Check each command against every other command
		for (uint8_t i = 0; i < numStatuses; i++) {
			for (uint8_t ii = i + 1; ii < numStatuses; ii++) {
				TEST_ASSERT_NOT_EQUAL(statusBitPositions[i], statusBitPositions[ii]);
			}
		}
	}

	void test_Status_OK(void) {
		testSingleStatus(0, Sys::STATUS_OK);
	}

	void test_Status_ERROR(void) {
		testSingleStatus(1, Sys::STATUS_ERROR);
	}

	void test_Status_AWAKE(void) {
		testSingleStatus(2, Sys::STATUS_AWAKE);
	}

	void test_Status_HEATING(void) {
		testSingleStatus(3, Sys::STATUS_HEATING);
	}

	void test_Status_FANNING(void) {
		testSingleStatus(4, Sys::STATUS_FANNING);
	}

	void test_Status_BUTTON_DOWN(void) {
		testSingleStatus(5, Sys::STATUS_BUTTON_DOWN);
	}

	void test_Status_SELECT(void) {
		testSingleStatus(6, Sys::STATUS_SELECT);
	}

	void test_Status_ACTIVE(void) {
		testSingleStatus(7, Sys::STATUS_ACTIVE);
	}

	void testSingleStatus(uint8_t bitPos, uint8_t status) {
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
