#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "filaments.h"
#include "thermistor.h"
#include <Arduino.h>
#include <stdint.h>

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
		Active,
		_Last
	};

	enum class Command : uint8_t {
		WakeUp,
		HeaterOn,
		HeaterOff,
		FanOn,
		FanOff,
		ButtonClicked,
		ButtonHeld,
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

	enum class Timers : uint8_t {
		InputPollingActive,
		InputPollingIdle,
		ScreenTimeout,
		HeaterTimeout,
		HeaterCooldown,
		SelectionTimeout,
		ButtonHold,
		_Last
	};

	// Global time.
	uint32_t currentTime;

	// Exhaust temperature delta.
	static constexpr uint8_t tempDelta = 5;	   // Degrees Celsius.

	// Timers.
	uint32_t timers[static_cast<uint8_t>(Timers::_Last)];
	uint32_t timerIntervals[static_cast<uint8_t>(Timers::_Last)];

	static constexpr uint32_t INPUT_POLL_ACTIVE_INTERVAL = 100UL;
	// Timer inputPollingActive{INPUT_POLL_ACTIVE_INTERVAL};
	// uint32_t timerInputPollingActive;

	static constexpr uint32_t INPUT_POLL_IDLE_INTERVAL = 1000UL * 60;
	// Timer inputPollingIdle{INPUT_POLL_IDLE_INTERVAL};
	// uint32_t timerInputPollingIdle;

	static constexpr uint32_t SCREEN_TIMEOUT_INTERVAL = 1000UL * 30;
	// Timer screenTimeout{SCREEN_TIMEOUT_INTERVAL};
	// uint32_t timerScreenTimeout;

	static constexpr uint32_t HEATER_TIMEOUT_INTERVAL = 1000UL * 60 * 2;
	// Timer heaterTimeout{HEATER_TIMEOUT_INTERVAL};
	// uint32_t timerHeaterTimeout;

	static constexpr uint32_t HEATER_COOLDOWN_TIME_INTERVAL = 1000UL * 60 * 2;
	// Timer heaterCooldown{HEATER_COOLDOWN_TIME_INTERVAL};
	// uint32_t timerHeaterCooldown;

	static constexpr uint32_t SELECTION_TIMEOUT_INTERVAL = 1000UL * 5;
	// Timer selectionTimeout{SELECTION_TIMEOUT_INTERVAL};
	// uint32_t timerSelectionTimeout;

	static constexpr uint32_t BUTTON_HOLD_TIMEOUT_INTERVAL = 800UL;
	// Timer buttonHold{BUTTON_HOLD_TIMEOUT_INTERVAL};
	// uint32_t timerButtonHold;

	// Status methods.
	void setStatus(Status status);
	void clearStatus(Status status);
	void toggleStatus(Status status);
	bool getStatus(Status status) const;

	// Command methods.
	void setCommand(Command command);
	void clearCommand(Command command);
	bool getCommand(Command command) const;
	bool checkCommand(Command command);

	// Dirty methods.
	void setDirty(Dirty dirty);
	void clearDirty(Dirty dirty);
	bool getDirty(Dirty dirty) const;
	bool checkDirty(Dirty dirty);
	void clearAllDirties();

	// Timer methods.
	bool checkTimer(Timers timerEnum) {
		if (currentTime >= timers[static_cast<uint8_t>(timerEnum)]
							   + Ops::timerIntervals[static_cast<uint8_t>(timerEnum)]) {
			timers[static_cast<uint8_t>(timerEnum)] = currentTime;
			return true;
		}
		return false;
	}

	bool getTimer(Timers timerEnum) {
		return (
			currentTime >= timers[static_cast<uint8_t>(timerEnum)]
							   + Ops::timerIntervals[static_cast<uint8_t>(timerEnum)]
		);
	}

	void resetTimer(Timers timerEnum) {
		timers[static_cast<uint8_t>(timerEnum)] = currentTime;
	}

	// Single template function that works with all enum types.
	template <typename T>
	static constexpr uint8_t getEnumBit(T bit) {
		return 1 << static_cast<uint8_t>(bit);
	}

	/**
	 * \brief Accepts a humidity reading from the sensor.
	 * Sets operations humidity if diffferent.
	 * \param humidity as %
	 * \return \c true if humidity value changed, \c false otherwise
	 * \note Sets Error status if sensor reading is invalid.
	 */
	bool checkHumidity(float humidity);

	/**
	 * \brief Gets the current humidity reading from the sensor
	 * \return Humidity as percentage (0-100)
	 * \note Returns 0 if no valid reading has been received
	 */
	uint8_t getHumidity() const;

	/**
	 * \brief Accepts a temperature reading from the sensor.
	 * Sets operations temperature if diffferent.
	 * \param temperature as °C.
	 * \return \c true if temperature value changed, \c false otherwise
	 * \note Sets Error status if sensor reading is invalid or out of range (0-100°C).
	 */
	bool checkTemperature(float temperature);

	/**
	 * \brief Gets the current temperature reading from the SHT31 sensor
	 * \return Temperature in Celsius
	 * \note Returns 99 if no valid reading has been received
	 */
	uint8_t getTemperature() const;

	/**
	 * \brief Reads and validates temperature from the NTC thermistor.
	 * Sets operations temperature if diffferent.
	 * \param value as 10bit ADC value.
	 * \return \c true if temperature value changed, \c false otherwise
	 * \note Sets Error status if thermistor reading is invalid or out of range (0-100°C).
	 */
	bool checkTherm(int8_t temperature);

	/**
	 * \brief Gets the current temperature reading from the NTC thermistor
	 * \return Temperature in Celsius
	 * \note Returns 99 if no valid reading has been received
	 */
	uint8_t getTherm() const;

	private:

	// Private constructor.
	Ops() : statuses(0), commands(0), dirties(0) {
		timerIntervals[static_cast<uint8_t>(Timers::InputPollingActive)] =
			INPUT_POLL_ACTIVE_INTERVAL;
		timerIntervals[static_cast<uint8_t>(Timers::InputPollingIdle)] = INPUT_POLL_IDLE_INTERVAL;
		timerIntervals[static_cast<uint8_t>(Timers::ScreenTimeout)]	   = SCREEN_TIMEOUT_INTERVAL;
		timerIntervals[static_cast<uint8_t>(Timers::HeaterTimeout)]	   = HEATER_TIMEOUT_INTERVAL;
		timerIntervals[static_cast<uint8_t>(Timers::HeaterCooldown)] =
			HEATER_COOLDOWN_TIME_INTERVAL;
		timerIntervals[static_cast<uint8_t>(Timers::SelectionTimeout)] = SELECTION_TIMEOUT_INTERVAL;
		timerIntervals[static_cast<uint8_t>(Timers::ButtonHold)] = BUTTON_HOLD_TIMEOUT_INTERVAL;

		timers[static_cast<uint8_t>(Timers::InputPollingActive)] = 0;
		timers[static_cast<uint8_t>(Timers::InputPollingIdle)]	 = 0;
		timers[static_cast<uint8_t>(Timers::ScreenTimeout)]		 = 0;
		timers[static_cast<uint8_t>(Timers::HeaterTimeout)]		 = 0;
		timers[static_cast<uint8_t>(Timers::HeaterCooldown)]	 = 0;
		timers[static_cast<uint8_t>(Timers::SelectionTimeout)]	 = 0;
		timers[static_cast<uint8_t>(Timers::ButtonHold)]		 = 0;
	}

	// Inputs.
	uint8_t sensHumid = 0;
	uint8_t sensTemp  = 99;
	uint8_t thermTemp = 99;

	uint8_t statuses = 0;
	uint8_t commands = 0;
	uint8_t dirties	 = 0;
};

#endif
