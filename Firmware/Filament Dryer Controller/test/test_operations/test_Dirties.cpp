#include "operations.h"
#include "test_operations.h"
#include <Arduino.h>
#include <unity.h>

using namespace test_Operations_Helpers;

namespace test_Dirties {
	unsigned char mask = 0b11111111;

	void test_Dirties() {
		RUN_TEST(test_Dirty_New);
		RUN_TEST(test_Dirty_Each);
	}

	void test_Dirty_New(void) {
		Ops& ops = Ops::getInstance();
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getDirtiesRaw(ops));
	}

	void test_Dirty_Each(void) {
		Ops& ops = Ops::getInstance();

		for (uint8_t i = 0; i < lastValue(Ops::Dirty{}); i++) {
			TEST_ASSERT_TRUE_MESSAGE(i < 8, "Too many enum values defined.");

			Ops::Dirty dirty = fromInt<Ops::Dirty>(i);
			uint8_t expected = (1 << i);

			ops.setDirty(dirty);

			TEST_ASSERT_TRUE(ops.getDirty(dirty));
			TEST_ASSERT_BITS(mask, expected, OpsTestAccess::getDirtiesRaw(ops));

			ops.clearDirty(dirty);
			TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getDirtiesRaw(ops));

			TEST_ASSERT_FALSE(ops.checkDirty(dirty));
			ops.setDirty(dirty);
			TEST_ASSERT_TRUE(ops.checkDirty(dirty));
			TEST_ASSERT_FALSE(ops.checkDirty(dirty));
			TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getDirtiesRaw(ops));

			// Reset for next iteration
			OpsTestAccess::setDirtiesRaw(ops, 0);
		}
	}

	void test_Dirty_ClearAll(void) {
		Ops& ops = Ops::getInstance();

		OpsTestAccess::setDirtiesRaw(ops, (uint8_t)-1);
		TEST_ASSERT_BITS_HIGH(mask, OpsTestAccess::getDirtiesRaw(ops));

		ops.clearAllDirties();
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getDirtiesRaw(ops));
	}
}
