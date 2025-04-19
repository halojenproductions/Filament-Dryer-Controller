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

void Ops::clearAllDirties() {
	dirties = 0;
}
