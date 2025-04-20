#include "filaments.h"
#include "temperature.h"
#include "timer.h"
#include <Arduino.h>
#include <stdint.h>

#ifndef OPERATIONS_H
#define OPERATIONS_H

// Forward declare the test access class
namespace test_Operations_Helpers {
	class OpsTestAccess;
}

class Ops {
	friend class test_Operations_Helpers::OpsTestAccess;

	public:

	// Singleton stuff.
	static Ops& getInstance() {
		static Ops instance;
		return instance;
	}

	Ops(const Ops&)			   = delete;
	void operator=(const Ops&) = delete;

	enum class Status : uint8_t {
		Ok,
		Error,
		ScreenAwake,
		Heating,
		Fanning,
		ButtonDown,
		Select,
		_Last
	};

	enum class Command : uint8_t {
		WakeUp,
		Heat,
		Fan,
		ButtonClick,
		ButtonHold,
		ButtonHoldHandled,	  // Yeah, it's confusing. I can't think of a better name.
		_Last
	};

	enum class Dirty : uint8_t {
		All,
		Filament,
		Temp,
		Humidity,
		_Last
	};

	OutTemp outTemp;
	int8_t inTemperature = 99;
	int8_t humidity		 = 99;
	int8_t FanSpeed		 = 0;

	// Timers.
	static constexpr uint32_t INPUT_POLL_TIME = 1000UL;
	Timer inputPolling{INPUT_POLL_TIME};

	static constexpr uint32_t SCREEN_TIMEOUT = 1000UL * 30;
	Timer screenTimeout{SCREEN_TIMEOUT};

	static constexpr uint32_t HEATER_TIMEOUT = 1000UL * 60 * 2;
	Timer heaterTimeout{HEATER_TIMEOUT};

	static constexpr uint32_t HEATER_COOLDOWN_TIME = 1000UL * 60 * 2;
	Timer heaterCooldown{HEATER_COOLDOWN_TIME};

	static constexpr uint32_t SELECTION_TIMEOUT = 1000UL * 5;
	Timer selectionTimeout{SELECTION_TIMEOUT};

	static constexpr uint32_t BUTTON_HOLD_TIMEOUT = 800UL;
	Timer buttonHold{BUTTON_HOLD_TIMEOUT};

	// Single template function that works with all enum types.
	template <typename T>
	static constexpr uint8_t getEnumBit(T bit) {
		return 1 << static_cast<uint8_t>(bit);
	}

	// Status functions.
	void setStatus(Status status);
	void clearStatus(Status status);
	void toggleStatus(Status status);
	bool getStatus(Status status) const;

	// Command functions.
	void setCommand(Command command);
	void clearCommand(Command command);
	bool getCommand(Command command) const;
	bool checkCommand(Command command);

	// Dirty functions.
	void setDirty(Dirty dirty);
	void clearDirty(Dirty dirty);
	bool getDirty(Dirty dirty) const;
	bool checkDirty(Dirty dirty);
	void clearAllDirties();

	private:

	// Private constructor
	Ops() : statuses(0), commands(0), dirties(0) {}

	uint8_t statuses = 0;
	uint8_t commands = 0;
	uint8_t dirties	 = 0;
};

#endif
