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
		ButtonHoldHandled,
		_Last
	};

	enum class Dirty : uint8_t {
		All,
		Top,
		Bottom,
		Temp,
		Humidity,
		_Last
	};

	OutTemp outTemp;								// Temperature in centigrade.
	Filament filament = Filaments::filaments[0];	// Default to PLA
	int inTemperature = 99;							// Temperature in centigrade.
	int humidity	  = 99;
	int FanSpeed;

	// Timers.
	Timer inputPolling	   = Timer(1000UL * 1);
	Timer screenTimeout	   = Timer(1000UL * 30);
	Timer heaterTimeout	   = Timer(1000UL * 60 * 2);
	Timer heaterCooldown   = Timer(1000UL * 60 * 2);
	Timer selectionTimeout = Timer(1000UL * 5);
	Timer buttonDebounce   = Timer(50);
	Timer buttonHold	   = Timer(800);

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

	// Dirty functions.
	void setDirty(Dirty dirty);
	void clearDirty(Dirty dirty);
	bool getDirty(Dirty dirty) const;
	void clearAllDirties();

	// Other functions.

	private:

	uint8_t statuses = 0;
	uint8_t commands = 0;
	uint8_t dirties	 = 0;
};

#endif
