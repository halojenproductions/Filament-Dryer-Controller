#include "controlLoop.h"

namespace ControlLoop {
	Ops& ops			 = Ops::getInstance();
	Filaments& filaments = Filaments::getInstance();

	void active() {
		if (ops.getHumidity() > filaments.getActive().humidity) {
			/// Moist.

			if (ops.getStatus(Ops::Status::Heating)) {
				/// Moist & heater is off.
				/// Heater safety timer.
				if (ops.heaterTimeout.check(ops.currentTime)) {
					// If the heater has been on too long, turn it off and start cooldown.
					heaterOff();
					ops.heaterCooldown.reset();
					ops.clearStatus(Ops::Status::Active);
					return;
				}

				/// Box up to temperature.
				if (ops.getTemperature() >= filaments.getActive().temperature) {
					// If the box is up to temperature: turn the heater off; turn the fan off;
					// set status to idle; get out of here.
					heaterOff();
					fanOff();
					ops.clearStatus(Ops::Status::Active);
					return;
				}

			} else {
				/// Moist & heater is off.
				if (ops.getTherm() < filaments.getActive().temperature) {
				}
			}

			/// Heater duty.
			heaterDuty();

		} else {
			/// Dry.

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

	void heaterDuty() {
		if (ops.getStatus(Ops::Status::Heating)
			&& ops.getTherm() >= ops.getTemperature() + ops.tempDelta) {
			// If thermistor temp is more than [delta] degrees above the sensor temperature,
			// turn it off.
			heaterOff();
		} else if (
			!ops.getStatus(Ops::Status::Heating)
			&& ops.getTherm() < ops.getTemperature() + ops.tempDelta
			&& ops.getStatus(Ops::Status::Fanning)
		) {
			heaterOn();
		}
	}

	void idle() {
		if (ops.getHumidity() > filaments.getActive().humidity) {
			// TODO Moist.
		} else {
		}
	}

	void heaterOn() {
		digitalWrite(Pins::pHeater, LOW);
		digitalWrite(Pins::pLedHeat, LOW);
		ops.clearStatus(Ops::Status::Heating);
	}

	void heaterOff() {
		digitalWrite(Pins::pHeater, HIGH);
		digitalWrite(Pins::pLedHeat, HIGH);
		ops.clearStatus(Ops::Status::Heating);
	}

	void fanOnLow() {
		// TODO
		analogWrite(Pins::pFan, 0);
		ops.clearStatus(Ops::Status::Fanning);
	}

	void fanOnHigh() {
		// TODO
		analogWrite(Pins::pFan, 0);
		ops.clearStatus(Ops::Status::Fanning);
	}

	void fanOff() {
		analogWrite(Pins::pFan, 0);
		ops.clearStatus(Ops::Status::Fanning);
	}
}
