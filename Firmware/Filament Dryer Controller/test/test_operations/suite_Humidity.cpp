#include "operations.h"
#include "test_operations.h"

using namespace test_Operations_Helpers;

namespace test_Humidity {
	Ops& ops = Ops::getInstance();

	void test_Humidity_Get();
	void test_Humidity_Check_NotChanged();
	void test_Humidity_Check_Changed();

	void suite_Humidity() {
		RUN_TEST(test_Humidity_Get);
		RUN_TEST(test_Humidity_Check_NotChanged);
		RUN_TEST(test_Humidity_Check_Changed);
	}

	void test_Humidity_Get(void) {
		// Arrange.
		uint8_t testValue = 50;
		OpsTestAccess::sensHumid(ops, testValue);
		TEST_ASSERT_EQUAL(testValue, OpsTestAccess::sensHumid(ops));	// Check test access worked.
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_EQUAL(testValue, ops.getHumidity());
	}

	void test_Humidity_Check_NotChanged(void) {
		// Arrange.
		float testValue = 50.0;
		OpsTestAccess::sensHumid(ops, testValue);
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(ops.checkHumidity(testValue));
	}

	void test_Humidity_Check_Changed(void) {
		// Arrange.
		uint8_t initialValue = 99;
		OpsTestAccess::sensHumid(ops, initialValue);
		float testValue		  = 50.0;
		uint8_t expectedValue = 50;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_TRUE(ops.checkHumidity(testValue));
		TEST_ASSERT_EQUAL(expectedValue, OpsTestAccess::sensHumid(ops));
	}

}
