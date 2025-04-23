#include "controlLoop.h"

namespace ControlLoop {
	Ops& ops			 = Ops::getInstance();
	Filaments& filaments = Filaments::getInstance();

	void controlLoop() {
		if (millis > 0) {
		}
		if (ops.getHumidity() <= filaments.getActive().humidity) {
			// We are dry.
			if (ops.getStatus(Ops::Status::Active)) {
				if (ops.getStatus(Ops::Status::Heating)) {
					// Maybe should just set it low every time, to be safe.
					heaterOff();
				}
				if (ops.getStatus(Ops::Status::Fanning)) {
					// Maybe should just set it low every time, to be safe.
					fanOff();
				}

				ops.clearStatus(Ops::Status::Active);
			}
		}
	}

	void active() {}

	void idle() {}

	void heaterOff() {
		digitalWrite(Pins::pHeater, LOW);
		digitalWrite(Pins::pLedHeat, LOW);
		ops.clearStatus(Ops::Status::Heating);
	}

	void fanOff() {
		analogWrite(Pins::pFan, 0);
		ops.clearStatus(Ops::Status::Fanning);
	}
}
