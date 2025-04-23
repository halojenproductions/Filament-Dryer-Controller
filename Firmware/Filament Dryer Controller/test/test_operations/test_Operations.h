#include "operations.h"
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

namespace suite_Humidity {
	void suite_Humidity();
}

namespace suite_Temperature {
	void suite_Temperature();
}

extern void setUp(void);
extern void tearDown(void);

namespace test_Operations_Helpers {
	constexpr byte mask = 0b11111111;

	template <typename T>
	constexpr uint8_t toInt(T enumValue) {
		return static_cast<uint8_t>(enumValue);
	}

	template <typename T>
	constexpr T fromInt(uint8_t i) {
		return static_cast<T>(i);
	}

	template <typename T>
	constexpr uint8_t lastValue(T) {
		return toInt(T::_Last);
	}

	class OpsTestAccess {
		public:

		static uint8_t statuses(const Ops& ops) {
			return ops.statuses;
		}

		static void statuses(Ops& ops, uint8_t value) {
			ops.statuses = value;
		}

		static uint8_t commands(const Ops& ops) {
			return ops.commands;
		}

		static void commands(Ops& ops, uint8_t value) {
			ops.commands = value;
		}

		static uint8_t dirties(const Ops& ops) {
			return ops.dirties;
		}

		static void dirties(Ops& ops, uint8_t value) {
			ops.dirties = value;
		}

		static uint8_t sensHumid(const Ops& ops) {
			return ops.sensHumid;
		}

		static void sensHumid(Ops& ops, uint8_t value) {
			ops.sensHumid = value;
		}
		static uint8_t sensTemp(const Ops& ops) {
			return ops.sensTemp;
		}

		static void sensTemp(Ops& ops, uint8_t value) {
			ops.sensTemp = value;
		}
	};
}

#endif
