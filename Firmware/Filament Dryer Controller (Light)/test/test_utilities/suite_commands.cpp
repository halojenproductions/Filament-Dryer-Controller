#include "test_utilities.h"
#include <Arduino.h>
#include <unity.h>

namespace suite_util_commands {
	using namespace Sys;
	using namespace Util;

	void command_max_8_defined();
	void command_each();
	void testCommand(uint16_t);

	void suite_commands() {
		RUN_TEST(command_max_8_defined);
		RUN_TEST(command_each);
	}

	// Tests.
	void command_max_8_defined(void) {
		TEST_ASSERT_LESS_OR_EQUAL_MESSAGE(8, Command::_Last, "Too many status bits defined.");
	}

	void command_each(void) {
		for (uint16_t i = 0; i < static_cast<uint16_t>(Command::_Last); i++) {
			testCommand(i);
			// Reset for next iteration.
			commands = 0;
		}
	}

	void testCommand(uint16_t commandValue) {
		Command command	 = (Command)commandValue;
		uint8_t expected = (1 << commandValue);

		// Set.
		setCommand(command);
		TEST_ASSERT_BITS(mask, expected, commands);
		// Get.
		TEST_ASSERT_TRUE(getCommand(command));
		// Clear.
		clearCommand(command);
		TEST_ASSERT_BITS_LOW(mask, commands);
		// Check.
		setCommand(command);
		TEST_ASSERT_TRUE(checkCommand(command));
		TEST_ASSERT_FALSE(checkCommand(command));
		TEST_ASSERT_BITS_LOW(mask, commands);
	}
}
