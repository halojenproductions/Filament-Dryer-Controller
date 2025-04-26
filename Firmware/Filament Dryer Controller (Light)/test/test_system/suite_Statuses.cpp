#include "test_system.h"

using namespace test_Operations_Helpers;

namespace suite_Statuses {

	void test_Statuses_Unique();
	void test_Status_Indexes();

	void suite_Statuses() {
		RUN_TEST(test_Statuses_Unique);
		RUN_TEST(test_Status_Indexes);
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

		assertArrayValuesUnique(statusBitPositions, numStatuses, "Status bits not unique");
	}

	void test_Status_Indexes(void) {
		TEST_ASSERT_EQUAL(0, Sys::STATUS_OK);
		TEST_ASSERT_EQUAL(1, Sys::STATUS_ERROR);
		TEST_ASSERT_EQUAL(2, Sys::STATUS_AWAKE);
		TEST_ASSERT_EQUAL(3, Sys::STATUS_HEATING);
		TEST_ASSERT_EQUAL(4, Sys::STATUS_FANNING);
		TEST_ASSERT_EQUAL(5, Sys::STATUS_BUTTON_DOWN);
		TEST_ASSERT_EQUAL(6, Sys::STATUS_SELECT);
		TEST_ASSERT_EQUAL(7, Sys::STATUS_ACTIVE);
	}

}
