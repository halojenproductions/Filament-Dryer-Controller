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
			Sys::Status::Ok,
			Sys::Status::Error,
			Sys::Status::ScreenAwake,
			Sys::Status::Heating,
			Sys::STATUS_FANNING,
			Sys::Status::ButtonDown,
			Sys::Status::Select,
			Sys::Status::Active
		};
		const uint8_t numStatuses = sizeof(statusBitPositions) / sizeof(statusBitPositions[0]);

		assertArrayValuesUnique(statusBitPositions, numStatuses, "Status bits not unique");
	}

	void test_Status_Indexes(void) {
		TEST_ASSERT_EQUAL(0, Sys::Status::Ok);
		TEST_ASSERT_EQUAL(1, Sys::Status::Error);
		TEST_ASSERT_EQUAL(2, Sys::Status::ScreenAwake);
		TEST_ASSERT_EQUAL(3, Sys::Status::Heating);
		TEST_ASSERT_EQUAL(4, Sys::STATUS_FANNING);
		TEST_ASSERT_EQUAL(5, Sys::Status::ButtonDown);
		TEST_ASSERT_EQUAL(6, Sys::Status::Select);
		TEST_ASSERT_EQUAL(7, Sys::Status::Active);
	}

}
