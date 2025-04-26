#include "test_utilities.h"

namespace suite_Humidity {
	void test_Humidity_Check_NotChanged();
	void test_Humidity_Check_Changed();
	void test_Humidity_Check_NaN();
	void test_Humidity_Check_UnderLimit();
	void test_Humidity_Check_OverLimit();

	void suite_Humidity() {
		RUN_TEST(test_Humidity_Check_NotChanged);
		RUN_TEST(test_Humidity_Check_Changed);
		RUN_TEST(test_Humidity_Check_NaN);
		RUN_TEST(test_Humidity_Check_UnderLimit);
		RUN_TEST(test_Humidity_Check_OverLimit);
	}

	void reset(void) {
		// Reset state before each test
		Sys::sensHumid = 50;
		Sys::statuses  = 0;
	}

	// Tests.
	void test_Humidity_Check_NotChanged(void) {
		reset();
		// Arrange.
		float testValue = 50.0;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(Util::checkHumidity(testValue));
	}

	void test_Humidity_Check_Changed(void) {
		reset();
		// Arrange.
		float testValue		  = 22.2;
		uint8_t expectedValue = 22;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_TRUE(Util::checkHumidity(testValue));
		TEST_ASSERT_EQUAL(expectedValue, Sys::sensHumid);
		TEST_ASSERT_FALSE(bitRead(Sys::statuses, Sys::STATUS_ERROR));
	}

	void test_Humidity_Check_NaN(void) {
		reset();
		// Arrange.
		float testValue		  = NAN;
		uint8_t expectedValue = 50;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(Util::checkHumidity(testValue));
		TEST_ASSERT_TRUE(bitRead(Sys::statuses, Sys::STATUS_ERROR));
		TEST_ASSERT_EQUAL(expectedValue, Sys::sensHumid);
	}

	void test_Humidity_Check_UnderLimit(void) {
		reset();
		// Arrange.
		float testValue		  = -0.1;
		uint8_t expectedValue = 50;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(Util::checkHumidity(testValue));
		TEST_ASSERT_TRUE(bitRead(Sys::statuses, Sys::STATUS_ERROR));
		TEST_ASSERT_EQUAL(expectedValue, Sys::sensHumid);
	}

	void test_Humidity_Check_OverLimit(void) {
		reset();
		// Arrange.
		float testValue		  = 100.1;
		uint8_t expectedValue = 50;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(Util::checkHumidity(testValue));
		TEST_ASSERT_TRUE(bitRead(Sys::statuses, Sys::STATUS_ERROR));
		TEST_ASSERT_EQUAL(expectedValue, Sys::sensHumid);
	}
}
