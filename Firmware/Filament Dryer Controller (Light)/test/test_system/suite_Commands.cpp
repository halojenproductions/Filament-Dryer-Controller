#include "test_system.h"
#include <Arduino.h>
#include <unity.h>
using namespace test_Operations_Helpers;

namespace suite_Commands {
	void test_Commands_Unique();
	void test_Command_Indexes();

	void suite_Commands() {
		RUN_TEST(test_Commands_Unique);
		RUN_TEST(test_Command_Indexes);
	}

	// Tests.
	void test_Commands_Unique() {
		// Create array of all command values
		const uint8_t commandBitPositions[] = {
			Sys::Command::WakeUp,
			Sys::COMMAND_HEATER_ON,
			Sys::COMMAND_HEATER_OFF,
			Sys::COMMAND_FAN_ON,
			Sys::COMMAND_FAN_OFF,
			Sys::COMMAND_BUTTON_CLICKED,
			Sys::COMMAND_BUTTON_HELD,
			Sys::Command::ButtonHoldHandled
		};
		const uint8_t numCommands = sizeof(commandBitPositions) / sizeof(commandBitPositions[0]);

		assertArrayValuesUnique(commandBitPositions, numCommands, "Command bits not unique");
	}

	void test_Command_Indexes(void) {
		TEST_ASSERT_EQUAL(0, Sys::Command::WakeUp);
		TEST_ASSERT_EQUAL(1, Sys::COMMAND_HEATER_ON);
		TEST_ASSERT_EQUAL(2, Sys::COMMAND_HEATER_OFF);
		TEST_ASSERT_EQUAL(3, Sys::COMMAND_FAN_ON);
		TEST_ASSERT_EQUAL(4, Sys::COMMAND_FAN_OFF);
		TEST_ASSERT_EQUAL(5, Sys::COMMAND_BUTTON_CLICKED);
		TEST_ASSERT_EQUAL(6, Sys::COMMAND_BUTTON_HELD);
		TEST_ASSERT_EQUAL(7, Sys::Command::ButtonHoldHandled);
	}
}
