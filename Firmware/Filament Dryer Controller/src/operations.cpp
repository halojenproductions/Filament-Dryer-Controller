#include "operations.h"

// Status functions.
void Ops::setStatus(Status flag) {
	statuses |= flag;
}

void Ops::clearStatus(Status flag) {
	statuses &= ~flag;
}

void Ops::toggleStatus(Status flag) {
	statuses ^= flag;
}

bool Ops::getStatus(Status flag) const {
	return statuses & flag;
}

unsigned char Ops::getStatusesRaw() const {
	return statuses;
}

// Command functions.
void Ops::setCommand(Command flag) {
	statuses |= flag;
}

void Ops::clearCommand(Command flag) {
	statuses &= ~flag;
}

bool Ops::getCommand(Command flag) const {
	return statuses & flag;
}

unsigned char Ops::getCommandsRaw() const {
	return statuses;
}
