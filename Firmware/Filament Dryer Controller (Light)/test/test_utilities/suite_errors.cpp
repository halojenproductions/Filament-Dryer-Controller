#include "test_utilities.h"

namespace suite_util_errors {
	using namespace Sys;
	using namespace Util;

	void errors_max_8_defined();
	void errors_each();
	void testError(uint16_t);

	void suite_Errors() {
		RUN_TEST(errors_max_8_defined);
		RUN_TEST(errors_each);
	}

	// Tests.
	void errors_max_8_defined(void) {
		TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(8, Error::_Last, "Too many error bits defined.");
	}

	void errors_each(void) {
		for (uint16_t i = 0; i < static_cast<uint16_t>(Error::_Last); i++) {
			testError(i);
			// Reset for next iteration.
			errors = 0;
		}
	}

	void testError(uint16_t errorValue) {
		Error error		 = (Error)errorValue;
		uint8_t expected = (1 << errorValue);

		if (error == Error::ActiveTimeout || error == Error::HeatingTimeout) {
			// Resettable errors.
			// Set.
			setError(error);
			TEST_ASSERT_BITS(mask, expected, errors);
			// Has.
			TEST_ASSERT_TRUE(hasError());
			// Get.
			TEST_ASSERT_TRUE(getError(error));
			// Clear.
			clearError(error);
			TEST_ASSERT_BITS_LOW(mask, errors);
			// Terminal error check.
			TEST_ASSERT_FALSE(terminalError());
		} else {
			// Terminal errors.
			// Set.
			setError(error);
			TEST_ASSERT_BITS(mask, expected, errors);
			// Has.
			TEST_ASSERT_TRUE(hasError());
			// Get.
			TEST_ASSERT_TRUE(getError(error));
			// NOT cleared.
			clearError(error);
			TEST_ASSERT_BITS(mask, expected, errors);
			// Terminal error check.
			TEST_ASSERT_TRUE(terminalError());
		}
	}
}
