#include "operations.h"
#include "test_operations.h"
#include <Arduino.h>
#include <unity.h>

using namespace test_Operations_Helpers;

namespace test_Commands {
	unsigned char mask = 0b11111111;

	void test_Commands() {
		RUN_TEST(test_Command_New);
		RUN_TEST(test_Command_Each);
	}

	void test_Command_New(void) {
		Ops ops;
		TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getCommandsRaw(ops));
	}

	void test_Command_Each(void) {
		Ops ops;

		for (uint8_t i = 0; i < lastValue(Ops::Command{}); i++) {
			TEST_ASSERT_TRUE_MESSAGE(i < 8, "Too many enum values defined.");

			Ops::Command command = fromInt<Ops::Command>(i);
			uint8_t expected	 = (1 << i);

			ops.setCommand(command);

			TEST_ASSERT_BITS(mask, expected, OpsTestAccess::getCommandsRaw(ops));
			TEST_ASSERT_TRUE(ops.getCommand(command));

			ops.clearCommand(command);
			TEST_ASSERT_BITS_LOW(mask, OpsTestAccess::getCommandsRaw(ops));
		}
	}
}
