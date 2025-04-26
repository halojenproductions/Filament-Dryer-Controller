#include "test_system.h"
#include <Arduino.h>
#include <unity.h>

using namespace test_Operations_Helpers;

namespace suite_Dirties {
	void test_Dirties_Unique();
	void test_Dirty_Indexes();


	void suite_Dirties() {
		RUN_TEST(test_Dirties_Unique);
		RUN_TEST(test_Dirty_Indexes);

	}

	// Tests.
	void test_Dirties_Unique() {
		// Create array of all command values
		const uint8_t dirtyBitPositions[] = {
			Sys::DIRTY_ALL,
			Sys::DIRTY_FILAMENT,
			Sys::DIRTY_TEMP,
			Sys::DIRTY_HUMIDITY,
		};
		const uint8_t numDirties = sizeof(dirtyBitPositions) / sizeof(dirtyBitPositions[0]);

		assertArrayValuesUnique(dirtyBitPositions, numDirties, "Dirty bits not unique");
	}

	void test_Dirty_Indexes(void) {
		TEST_ASSERT_EQUAL(0, Sys::DIRTY_ALL);
		TEST_ASSERT_EQUAL(1, Sys::DIRTY_FILAMENT);
		TEST_ASSERT_EQUAL(2, Sys::DIRTY_TEMP);
		TEST_ASSERT_EQUAL(3, Sys::DIRTY_HUMIDITY);
	}

}
