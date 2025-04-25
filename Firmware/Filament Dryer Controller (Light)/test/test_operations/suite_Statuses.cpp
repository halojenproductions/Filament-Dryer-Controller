#include "test_operations.h"
#include <Arduino.h>
#include <unity.h>

using namespace test_Operations_Helpers;

namespace suite_Statuses {
	Ops& ops = Ops::getInstance();

	void test_Status_New();
	void test_Status_Each();

	void suite_Statuses() {
		RUN_TEST(test_Status_New);
		RUN_TEST(test_Status_Each);
	}

	// Tests.
	void test_Status_New(void) {
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::statuses(ops));
	}

	void test_Status_Each(void) {
		for (uint8_t i = 0; i < lastValue(Ops::Status{}); i++) {
			TEST_ASSERT_TRUE_MESSAGE(i < 8, "Too many enum values defined.");

			Ops::Status status = fromInt<Ops::Status>(i);
			uint8_t expected   = (1 << i);

			ops.setStatus(status);

			TEST_ASSERT_BITS(mask, expected, OpsTestAccess::statuses(ops));
			TEST_ASSERT_TRUE(bitRead(status));

			bitClear(status);
			TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::statuses(ops));

			ops.toggleStatus(status);
			TEST_ASSERT_BITS(mask, expected, OpsTestAccess::statuses(ops));
			TEST_ASSERT_TRUE(bitRead(status));

			// Reset for next iteration
			OpsTestAccess::statuses(ops, 0);
		}
	}
}
