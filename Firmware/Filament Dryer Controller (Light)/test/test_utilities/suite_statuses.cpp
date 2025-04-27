#include "test_utilities.h"

namespace suite_util_statuses {
	using namespace Sys;
	using namespace Util;

	void statuses_max_8_defined();
	void statuses_each();
	void testStatus(uint16_t statusValue);

	void suite_Statuses() {
		RUN_TEST(statuses_max_8_defined);
		RUN_TEST(statuses_each);
	}

	// Tests.
	void statuses_max_8_defined(void) {
		TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(8, Status::_Last, "Too many status bits defined.");
	}

	void statuses_each(void) {
		for (uint16_t i = 0; i < static_cast<uint16_t>(Status::_Last); i++) {
			testStatus(i);
			// Reset for next iteration.
			statuses = 0;
		}
	}

	void testStatus(uint16_t statusValue) {
		Status status	 = (Status)statusValue;
		uint8_t expected = (1 << statusValue);

		// Set.
		setStatus(status);
		TEST_ASSERT_BITS(mask, expected, statuses);
		// Get.
		TEST_ASSERT_TRUE(getStatus(status));
		// Clear.
		clearStatus(status);
		TEST_ASSERT_BITS_LOW(mask, statuses);
	}

}
