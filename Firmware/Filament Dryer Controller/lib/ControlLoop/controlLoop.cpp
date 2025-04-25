#include "controlLoop.h"

namespace ControlLoop {
	Ops& ops			 = Ops::getInstance();
	Filaments& filaments = Filaments::getInstance();

	void active() {
		// Serial.println("Active");
		if (ops.getHumidity() > filaments.getActive().humidity) {
			/// Moist.

			if (ops.getStatus(Ops::Status::Heating)) {
				/// Moist & heater is off.
				/// Heater safety timer.
				// if (ops.heaterTimeout.check(ops.currentTime)) {
				if (ops.getTimer(Ops::Timers::HeaterTimeout)) {
					// If the heater has been on too long, turn it off and start cooldown.
					heaterOff();
					// ops.heaterCooldown.reset();
					ops.resetTimer(Ops::Timers::HeaterCooldown);
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
			}

			/// Heater duty.
			heaterDuty();

		} else {
			/// Dry.

			heaterOff();
			fanOff();
			// ops.inputPollingIdle.reset();
			ops.resetTimer(Ops::Timers::InputPollingIdle);
			ops.clearStatus(Ops::Status::Active);
		}
	}

	void idle() {
		if (ops.getStatus(Ops::Status::Error) /*|| !ops.heaterCooldown.get(ops.currentTime)*/) {
			// Get out.
			return;
		}
		if (ops.getHumidity() > filaments.getActive().humidity) {
			/// Moist.
			fanOnHigh();
			heaterOn();
			ops.setStatus(Ops::Status::Active);
		} else {
		}
	}

	void heaterDuty() {
		if (ops.getStatus(Ops::Status::Heating)
			&& ops.getTherm() >= filaments.getActive().temperature + ops.tempDelta) {
			// If thermistor temp is more than [delta] degrees above the sensor temperature,
			// turn it off.
			heaterOff();
		} else if (!ops.getStatus(Ops::Status::Heating)
				   && ops.getTherm() < filaments.getActive().temperature + ops.tempDelta
				   && ops.getStatus(Ops::Status::Fanning)) {
			heaterOn();
		}
	}

	void heaterOn() {
		digitalWrite(Pins::pHeater, LOW);
		digitalWrite(Pins::pLedHeat, LOW);
		// ops.inputPollingActive.reset();
		ops.resetTimer(Ops::Timers::InputPollingActive);
		ops.clearStatus(Ops::Status::Heating);
	}

	void heaterOff() {
		digitalWrite(Pins::pHeater, HIGH);
		digitalWrite(Pins::pLedHeat, HIGH);
		ops.clearStatus(Ops::Status::Heating);
	}

	void fanOnLow() {
		// TODO scale to 255
		analogWrite(Pins::pFan, 10);
		ops.clearStatus(Ops::Status::Fanning);
	}

	void fanOnHigh() {
		// TODO scale to 255
		analogWrite(Pins::pFan, 50);
		ops.clearStatus(Ops::Status::Fanning);
	}

	void fanOff() {
		analogWrite(Pins::pFan, 0);
		ops.clearStatus(Ops::Status::Fanning);
	}
}
