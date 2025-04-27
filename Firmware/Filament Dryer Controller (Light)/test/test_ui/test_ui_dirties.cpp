#include "test_ui.h"
#include <Arduino.h>
#include <unity.h>

namespace test_ui_dirties {
	using namespace UI;
	constexpr byte mask = 0b11111111;

	void dirties_max_8_defined();
	void dirties_Each();
	void dirties_ClearAll();
	void testDirty(uint8_t dirtyValue);

	void suite_Dirties() {
		RUN_TEST(dirties_max_8_defined);
		RUN_TEST(dirties_Each);
		RUN_TEST(dirties_ClearAll);
	}

	// Tests.
	void dirties_max_8_defined(void) {
		TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(8, Dirty::_Last, "Too many dirty bits defined.");
	}

	void dirties_Each(void) {
		for (uint16_t i = 0; i < Dirty::_Last; i++) {
			testDirty(i);
			// Reset for next iteration.
			dirties = 0;
		}
	}

	void dirties_ClearAll(void) {
		dirties = (uint8_t)-1;
		TEST_ASSERT_BITS_HIGH(mask, dirties);

		clearDirties();
		TEST_ASSERT_BITS_LOW(mask, dirties);
	}

	void testDirty(uint8_t dirtyValue) {
		Dirty dirty		 = (Dirty)dirtyValue;
		uint8_t expected = (1 << dirtyValue);

		// Set.
		setDirty(dirty);
		TEST_ASSERT_BITS(mask, expected, dirties);
		// Get.
		TEST_ASSERT_TRUE(getDirty(dirty));
		// Clear.
		clearDirty(dirty);
		TEST_ASSERT_BITS_LOW(mask, dirties);
		// Check.
		setDirty(dirty);
		TEST_ASSERT_TRUE(checkDirty(dirty));
		TEST_ASSERT_FALSE(checkDirty(dirty));
		TEST_ASSERT_BITS_LOW(mask, dirties);
	}

}
