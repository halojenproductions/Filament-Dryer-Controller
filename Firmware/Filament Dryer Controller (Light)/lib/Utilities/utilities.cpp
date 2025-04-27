#include "utilities.h"

using namespace Sys;

namespace Util {

	// Timer methods.
	bool checkTimer(Timer& timer) {
		return timer.check(currentTime);
	}

	bool getTimer(Timer& timer) {
		return timer.get(currentTime);
	}

	void resetTimer(Timer& timer) {
		timer.reset(currentTime);
	}

	// Inputs.
	bool checkHumidity(float humidity) {
		// Validate the value.
		if (isnan(humidity) || humidity < 0 || humidity > 100) {
			setStatus(Sys::Status::Error);
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
			setStatus(Sys::Status::Error);
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
			setStatus(Sys::Status::Error);
			return false;
		}

		// If the value is different from ops, set ops and return true.
		if (temperature != thermTemp) {
			thermTemp = temperature;
			return true;
		}
		return false;
	}

	// Status functions.
	void setStatus(Status status) {
		bitSet(statuses, static_cast<uint8_t>(status));
	}

	void clearStatus(Status status) {
		bitClear(statuses, static_cast<uint8_t>(status));
	}

	bool getStatus(Status status) {
		return bitRead(statuses, static_cast<uint8_t>(status));
	}

	// Command functions.
	void setCommand(Command command) {
		bitSet(commands, static_cast<uint8_t>(command));
	}

	void clearCommand(Command command) {
		bitClear(commands, static_cast<uint8_t>(command));
	}

	bool getCommand(Command command) {
		return bitRead(commands, static_cast<uint8_t>(command));
	}

	bool checkCommand(Command command) {
		if (getCommand(command)) {
			clearCommand(command);
			return true;
		}
		return false;
	}

}
