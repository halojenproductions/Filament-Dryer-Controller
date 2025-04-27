#include "test_utilities.h"

namespace suite_Temperature {
	void Temperature_Check_NotChanged();
	void Temperature_Check_Changed();
	void Temperature_Check_NaN();
	void Temperature_Check_UnderLimit();
	void Temperature_Check_OverLimit();

	void suite_Temperature() {
		RUN_TEST(Temperature_Check_NotChanged);
		RUN_TEST(Temperature_Check_Changed);
		RUN_TEST(Temperature_Check_NaN);
		RUN_TEST(Temperature_Check_UnderLimit);
		RUN_TEST(Temperature_Check_OverLimit);
	}

	void reset(void) {
		// Reset state before each test
		Sys::sensTemp = 50;
		Sys::statuses = 0;
	}

	// Tests.
	void Temperature_Check_NotChanged(void) {
		reset();
		// Arrange.
		float testValue = 50.0;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(Util::checkTemperature(testValue));
	}

	void Temperature_Check_Changed(void) {
		reset();
		// Arrange.
		float testValue		  = 22.2;
		uint8_t expectedValue = 22;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_TRUE(Util::checkTemperature(testValue));
		TEST_ASSERT_EQUAL(expectedValue, Sys::sensTemp);
		TEST_ASSERT_FALSE(Util::getStatus(Sys::Status::Error));
	}

	void Temperature_Check_NaN(void) {
		reset();
		// Arrange.
		float testValue		  = NAN;
		uint8_t expectedValue = 50;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(Util::checkTemperature(testValue));
		TEST_ASSERT_TRUE(Util::getStatus(Sys::Status::Error));
		TEST_ASSERT_EQUAL(expectedValue, Sys::sensTemp);
	}

	void Temperature_Check_UnderLimit(void) {
		reset();
		// Arrange.
		float testValue		  = -0.1;
		uint8_t expectedValue = 50;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(Util::checkTemperature(testValue));
		TEST_ASSERT_TRUE(Util::getStatus(Sys::Status::Error));
		TEST_ASSERT_EQUAL(expectedValue, Sys::sensTemp);
	}

	void Temperature_Check_OverLimit(void) {
		reset();
		// Arrange.
		float testValue		  = 100.1;
		uint8_t expectedValue = 50;
		// Act & assert together because it's my project and i can do what i want.
		TEST_ASSERT_FALSE(Util::checkTemperature(testValue));
		TEST_ASSERT_TRUE(Util::getStatus(Sys::Status::Error));
		TEST_ASSERT_EQUAL(expectedValue, Sys::sensTemp);
	}
}
