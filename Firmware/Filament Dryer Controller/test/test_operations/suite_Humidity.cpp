#include "test_operations.h"

using namespace test_Operations_Helpers;

namespace suite_Humidity {
	Ops& ops = Ops::getInstance();

	void test_Humidity_Get();
	void test_Humidity_Check_NotChanged();
	void test_Humidity_Check_Changed();
	void test_Humidity_Check_NaN();
	void test_Humidity_Check_UnderLimit();
	void test_Humidity_Check_OverLimit();

	void suite_Humidity() {
		RUN_TEST(test_Humidity_Get);
		RUN_TEST(test_Humidity_Check_NotChanged);
		RUN_TEST(test_Humidity_Check_Changed);
		RUN_TEST(test_Humidity_Check_NaN);
		RUN_TEST(test_Humidity_Check_UnderLimit);
		RUN_TEST(test_Humidity_Check_OverLimit);
	}

	void reset(void) {
		// Reset state before each test
		OpsTestAccess::statuses(ops, 0);
		OpsTestAccess::sensHumid(ops, 50);
	}

	// Tests.
	void test_Humidity_Get(void) {
		reset();
		// Arrange.
		uint8_t expectedValue = 50;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_EQUAL(expectedValue, ops.getHumidity());
	}

	void test_Humidity_Check_NotChanged(void) {
		reset();
		// Arrange.
		float testValue = 50.0;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(ops.checkHumidity(testValue));
	}

	void test_Humidity_Check_Changed(void) {
		reset();
		// Arrange.
		float testValue		  = 22.2;
		uint8_t expectedValue = 22;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_TRUE(ops.checkHumidity(testValue));
		TEST_ASSERT_EQUAL(expectedValue, OpsTestAccess::sensHumid(ops));
	}

	void test_Humidity_Check_NaN(void) {
		reset();
		// Arrange.
		float testValue		  = NAN;
		uint8_t expectedValue = 50;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(ops.checkHumidity(testValue));
		TEST_ASSERT_TRUE(ops.getStatus(Ops::Status::Error));
		TEST_ASSERT_EQUAL(expectedValue, OpsTestAccess::sensHumid(ops));
	}

	void test_Humidity_Check_UnderLimit(void) {
		reset();
		// Arrange.
		float testValue		  = -0.1;
		uint8_t expectedValue = 50;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(ops.checkHumidity(testValue));
		TEST_ASSERT_TRUE(ops.getStatus(Ops::Status::Error));
		TEST_ASSERT_EQUAL(expectedValue, OpsTestAccess::sensHumid(ops));
	}

	void test_Humidity_Check_OverLimit(void) {
		reset();
		// Arrange.
		float testValue		  = 100.1;
		uint8_t expectedValue = 50;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(ops.checkHumidity(testValue));
		TEST_ASSERT_TRUE(ops.getStatus(Ops::Status::Error));
		TEST_ASSERT_EQUAL(expectedValue, OpsTestAccess::sensHumid(ops));
	}
}
