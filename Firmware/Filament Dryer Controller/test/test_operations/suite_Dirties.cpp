#include "test_operations.h"
#include <Arduino.h>
#include <unity.h>

using namespace test_Operations_Helpers;

namespace suite_Dirties {
	Ops& ops = Ops::getInstance();

	void test_Dirty_New();
	void test_Dirty_Each();

	void suite_Dirties() {
		RUN_TEST(test_Dirty_New);
		RUN_TEST(test_Dirty_Each);
	}

	// Tests.
	void test_Dirty_New(void) {
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::dirties(ops));
	}

	void test_Dirty_Each(void) {
		for (uint8_t i = 0; i < lastValue(Ops::Dirty{}); i++) {
			TEST_ASSERT_TRUE_MESSAGE(i < 8, "Too many enum values defined.");

			Ops::Dirty dirty = fromInt<Ops::Dirty>(i);
			uint8_t expected = (1 << i);

			// Set.
			ops.setDirty(dirty);
			TEST_ASSERT_BITS(mask, expected, OpsTestAccess::dirties(ops));
			// Get.
			TEST_ASSERT_TRUE(ops.getDirty(dirty));
			// Clear.
			ops.clearDirty(dirty);
			TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::dirties(ops));
			// Check.
			ops.setDirty(dirty);
			TEST_ASSERT_TRUE(ops.checkDirty(dirty));
			TEST_ASSERT_FALSE(ops.checkDirty(dirty));
			TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::dirties(ops));

			// Reset for next iteration
			OpsTestAccess::dirties(ops, 0);
		}
	}

	void test_Dirty_ClearAll(void) {
		OpsTestAccess::dirties(ops, (uint8_t)-1);
		TEST_ASSERT_BITS_HIGH(mask, OpsTestAccess::dirties(ops));

		ops.clearAllDirties();
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::dirties(ops));
	}
}
