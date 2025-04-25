#include "test_operations.h"
#include <Arduino.h>
#include <unity.h>

using namespace test_Operations_Helpers;

namespace suite_Commands {
	Ops& ops = Ops::getInstance();

	void test_Command_New();
	void test_Command_Each();

	void suite_Commands() {
		RUN_TEST(test_Command_New);
		RUN_TEST(test_Command_Each);
	}

	// Tests.
	void test_Command_New(void) {
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::commands(ops));
	}

	void test_Command_Each(void) {
		for (uint8_t i = 0; i < lastValue(Ops::Command{}); i++) {
			TEST_ASSERT_TRUE_MESSAGE(i < 8, "Too many enum values defined.");

			Ops::Command command = fromInt<Ops::Command>(i);
			uint8_t expected	 = (1 << i);

			// Set.
			ops.setCommand(command);
			TEST_ASSERT_BITS(mask, expected, OpsTestAccess::commands(ops));
			// Get.
			TEST_ASSERT_TRUE(ops.getCommand(command));
			// Clear.
			ops.clearCommand(command);
			TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::commands(ops));

			// Check.
			ops.setCommand(command);
			TEST_ASSERT_TRUE(ops.checkCommand(command));
			TEST_ASSERT_FALSE(ops.checkCommand(command));
			TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::commands(ops));

			// Reset for next iteration
			OpsTestAccess::commands(ops, 0);
		}
	}
}
