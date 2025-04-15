#include "status.h"

void Status::set(Flags flag) {
	status |= flag;
}

void Status::clear(Flags flag) {
	status &= ~flag;
}

void Status::toggle(Flags flag) {
	status ^= flag;
}

bool Status::isSet(Flags flag) const {
	return status & flag;
}

unsigned char Status::getRaw() const {
	return status;
}
