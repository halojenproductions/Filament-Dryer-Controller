#include "operations.h"

// Status functions.
void Ops::setStatus(Status status) {
	statuses |= getEnumBit(status);
}

void Ops::clearStatus(Status status) {
	statuses &= ~getEnumBit(status);
}

void Ops::toggleStatus(Status status) {
	statuses ^= getEnumBit(status);
}

bool Ops::getStatus(Status status) const {
	return statuses & getEnumBit(status);
}

// Command functions.
void Ops::setCommand(Command command) {
	commands |= getEnumBit(command);
}

void Ops::clearCommand(Command command) {
	commands &= ~getEnumBit(command);
}

bool Ops::getCommand(Command command) const {
	return commands & getEnumBit(command);
}

bool Ops::checkCommand(Command command) {
	if (commands & getEnumBit(command)) {
		commands &= ~getEnumBit(command);
		return true;
	}
	return false;
}

// Dirty functions.
void Ops::setDirty(Dirty dirty) {
	dirties |= getEnumBit(dirty);
}

void Ops::clearDirty(Dirty dirty) {
	dirties &= ~getEnumBit(dirty);
}

bool Ops::getDirty(Dirty dirty) const {
	return dirties & getEnumBit(dirty);
}

bool Ops::checkDirty(Dirty dirty) {
	if (dirties & getEnumBit(dirty)) {
		dirties &= ~getEnumBit(dirty);
		return true;
	}
	return false;
}

void Ops::clearAllDirties() {
	dirties = 0;
}

// Inputs.
bool Ops::checkHumidity(float humidity) {
	// Validate the value.
	if (isnan(humidity) || humidity < 0 || humidity > 100) {
		setStatus(Ops::Status::Error);
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

uint8_t Ops::getHumidity() const {
	return sensHumid;
}

bool Ops::checkTemperature(float temperature) {
	// Validate the value.
	if (isnan(temperature) || temperature < 0 || temperature > 100) {
		setStatus(Ops::Status::Error);
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

uint8_t Ops::getTemperature() const {
	return sensTemp;
}

bool Ops::checkTherm(int8_t temperature) {
	// Validate the value.
	if (temperature < 0 || temperature > 100) {
		setStatus(Ops::Status::Error);
		return false;
	}

	// If the value is different from ops, set ops and return true.
	if (temperature != thermTemp) {
		thermTemp = temperature;
		return true;
	}
	return false;
}

uint8_t Ops::getTherm() const {
	return thermTemp;
}

