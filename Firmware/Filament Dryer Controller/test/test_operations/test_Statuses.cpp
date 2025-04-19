#include "operations.h"
#include "test_operations.h"
#include <Arduino.h>
#include <unity.h>

using namespace test_Operations_Helpers;

namespace test_Statuses {
	unsigned char mask = 0b11111111;

	void test_Statuses() {
		RUN_TEST(test_Status_New);
		RUN_TEST(test_Status_First);
		RUN_TEST(test_Status_Last);
		RUN_TEST(test_Status_Each);
	}

	void test_Status_New(void) {
		Ops ops;
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getStatusesRaw(ops));
	}

	void test_Status_First(void) {
		Ops::Status status	   = Ops::Status::Ok;
		unsigned char expected = 0b00000001;
		Ops ops;

		ops.setStatus(status);
		TEST_ASSERT_BITS(mask, expected, OpsTestAccess::getStatusesRaw(ops));
		TEST_ASSERT_TRUE(ops.getStatus(status));

		ops.clearStatus(status);
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getStatusesRaw(ops));
		TEST_ASSERT_FALSE(ops.getStatus(status));

		ops.toggleStatus(status);
		TEST_ASSERT_BITS(mask, expected, OpsTestAccess::getStatusesRaw(ops));
		TEST_ASSERT_TRUE(ops.getStatus(status));
	}

	void test_Status_Last(void) {
		Ops::Status status	   = Ops::Status::Select;
		unsigned char expected = 0b01000000;
		Ops ops;

		ops.setStatus(status);
		TEST_ASSERT_BITS(mask, expected, OpsTestAccess::getStatusesRaw(ops));
		TEST_ASSERT_TRUE(ops.getStatus(status));

		ops.clearStatus(status);
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getStatusesRaw(ops));
		TEST_ASSERT_FALSE(ops.getStatus(status));

		ops.toggleStatus(status);
		TEST_ASSERT_BITS(mask, expected, OpsTestAccess::getStatusesRaw(ops));
		TEST_ASSERT_TRUE(ops.getStatus(status));
	}

	void test_Status_Each(void) {
		for (uint8_t i = 0; i < lastValue(Ops::Status{}); i++) {
			TEST_ASSERT_TRUE_MESSAGE(i < 8, "Too many enum values defined.");

			Ops ops;
			Ops::Status status = fromInt<Ops::Status>(i);
			uint8_t expected   = (1 << i);

			ops.setStatus(status);

			TEST_ASSERT_BITS(mask, expected, OpsTestAccess::getStatusesRaw(ops));
			TEST_ASSERT_TRUE(ops.getStatus(status));

			ops.clearStatus(status);
			TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getStatusesRaw(ops));

			ops.toggleStatus(status);
			TEST_ASSERT_BITS(mask, expected, OpsTestAccess::getStatusesRaw(ops));
			TEST_ASSERT_TRUE(ops.getStatus(status));
		}
	}
}
