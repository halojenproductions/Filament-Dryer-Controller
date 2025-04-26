#include "system.h"
#include "utilities.h"
#include <Arduino.h>
#include <unity.h>

#ifndef TEST_OPERATIONS_H
#define TEST_OPERATIONS_H

namespace suite_Statuses {
	void suite_Statuses();
}

namespace suite_Commands {
	void suite_Commands();
}

namespace suite_Dirties {
	void suite_Dirties();
}

namespace suite_Timers {
	void suite_Timers();
}

extern void setUp(void);
extern void tearDown(void);

namespace test_Operations_Helpers {
	constexpr byte mask = 0b11111111;

	template <typename T>
	void assertArrayValuesUnique(
		const T array[], const uint8_t size, const char* message = "Array values not unique"
	) {
		for (uint8_t i = 0; i < size; i++) {
			for (uint8_t ii = i + 1; ii < size; ii++) {
				TEST_ASSERT_NOT_EQUAL_MESSAGE(array[i], array[ii], message);
			}
		}
	}
}

#endif
