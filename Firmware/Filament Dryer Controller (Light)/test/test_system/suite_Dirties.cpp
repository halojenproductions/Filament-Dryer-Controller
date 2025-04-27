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
			UI::Dirty::All,
			UI::Dirty::Filament,
			UI::Dirty::Temp,
			UI::Dirty::Humidity,
		};
		const uint8_t numDirties = sizeof(dirtyBitPositions) / sizeof(dirtyBitPositions[0]);

		assertArrayValuesUnique(dirtyBitPositions, numDirties, "Dirty bits not unique");
	}

	void test_Dirty_Indexes(void) {
		TEST_ASSERT_EQUAL(0, UI::Dirty::All);
		TEST_ASSERT_EQUAL(1, UI::Dirty::Filament);
		TEST_ASSERT_EQUAL(2, UI::Dirty::Temp);
		TEST_ASSERT_EQUAL(3, UI::Dirty::Humidity);
	}

}
