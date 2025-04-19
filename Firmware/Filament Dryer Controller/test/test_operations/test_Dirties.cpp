#include "operations.h"
#include "test_operations.h"
#include <Arduino.h>
#include <unity.h>

using namespace test_Operations_Helpers;

namespace test_Dirties {
	unsigned char mask = 0b11111111;

	void test_Dirties() {
		RUN_TEST(test_Dirty_New);
		RUN_TEST(test_Dirty_First);
		RUN_TEST(test_Dirty_Last);
		RUN_TEST(test_Dirty_Each);
	}

	void test_Dirty_New(void) {
		Ops ops;
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getDirtiesRaw(ops));
	}

	void test_Dirty_First(void) {
		Ops::Dirty dirty	   = Ops::Dirty::All;
		unsigned char expected = 0b00000001;
		Ops ops;

		ops.setDirty(dirty);
		TEST_ASSERT_BITS(mask, expected, OpsTestAccess::getDirtiesRaw(ops));
		TEST_ASSERT_TRUE(ops.getDirty(dirty));

		ops.clearDirty(dirty);
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getDirtiesRaw(ops));
		TEST_ASSERT_FALSE(ops.getDirty(dirty));
	}

	void test_Dirty_Last(void) {
		Ops::Dirty dirty	   = Ops::Dirty::Humidity;
		unsigned char expected = 0b00010000;
		Ops ops;

		ops.setDirty(dirty);
		TEST_ASSERT_BITS(mask, expected, OpsTestAccess::getDirtiesRaw(ops));
		TEST_ASSERT_TRUE(ops.getDirty(dirty));

		ops.clearDirty(dirty);
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getDirtiesRaw(ops));
		TEST_ASSERT_FALSE(ops.getDirty(dirty));
	}

	void test_Dirty_Each(void) {
		Ops ops;

		for (uint8_t i = 0; i < lastValue(Ops::Dirty{}); i++) {
			TEST_ASSERT_TRUE_MESSAGE(i < 8, "Too many enum values defined.");

			Ops::Dirty dirty = fromInt<Ops::Dirty>(i);
			uint8_t expected = (1 << i);

			ops.setDirty(dirty);

			TEST_ASSERT_TRUE(ops.getDirty(dirty));
			TEST_ASSERT_BITS(mask, expected, OpsTestAccess::getDirtiesRaw(ops));

			ops.clearDirty(dirty);
			TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getDirtiesRaw(ops));
		}
	}

	void test_Dirty_ClearAll(void) {
		Ops ops;

		OpsTestAccess::setDirtiesRaw(ops, (uint8_t)-1);
		TEST_ASSERT_BITS_HIGH(mask, OpsTestAccess::getDirtiesRaw(ops));

		ops.clearAllDirties();
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getDirtiesRaw(ops));
	}
}
