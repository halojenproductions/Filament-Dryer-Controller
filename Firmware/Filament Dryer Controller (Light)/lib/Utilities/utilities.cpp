#include "utilities.h"

using namespace Sys;

namespace Util {
	bool bitCheck(uint8_t& value, uint8_t bitPos) {
		if (bitRead(value, bitPos) == 1) {
			bitClear(value, bitPos);
			return true;
		}
		return false;
	}

	void bitClearAll(uint8_t& value) {
		value = 0;
	}

	// Timer methods.
	bool checkTimer(uint8_t index) {
		if (currentTime >= timers[index] + timerIntervals[index]) {
			timers[index] = currentTime;
			return true;
		}
		return false;
	}

	bool getTimer(uint8_t& index) {
		return (currentTime >= timers[index] + timerIntervals[index]);
	}

	void resetTimer(uint8_t& index) {
		timers[index] = currentTime;
	}

	// Inputs.
	bool checkHumidity(float humidity) {
		// Validate the value.
		if (isnan(humidity) || humidity < 0 || humidity > 100) {
			bitSet(statuses, STATUS_ERROR);
			return false;
		}

		int8_t humidValue = static_cast<int8_t>(humidity);
		// If the value is different from ops, set ops and return true.
		if (humidValue != sensHumid) {
			sensHumid = humidValue;
			return true;
		}
		return false;
	}

	bool checkTemperature(float temperature) {
		// Validate the value.
		if (isnan(temperature) || temperature < 0 || temperature > 100) {
			bitSet(statuses, STATUS_ERROR);
			return false;
		}

		int8_t tempValue = static_cast<int8_t>(temperature);
		// If the value is different from ops, set ops and return true.
		if (tempValue != sensTemp) {
			sensTemp = tempValue;
			return true;
		}
		return false;
	}

	bool checkTherm(int8_t temperature) {
		// Validate the value.
		if (temperature < 0 || temperature > 100) {
			bitSet(statuses, STATUS_ERROR);
			return false;
		}

		// If the value is different from ops, set ops and return true.
		if (temperature != thermTemp) {
			thermTemp = temperature;
			return true;
		}
		return false;
	}

}
