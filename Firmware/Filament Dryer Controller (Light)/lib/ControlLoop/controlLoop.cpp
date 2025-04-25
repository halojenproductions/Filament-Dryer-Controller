#include "controlLoop.h"

namespace ControlLoop {

	void active() {
		// Serial.println("Active");
		if (Sys::sensHumid > Filaments::activeFilament.humidity) {
			/// Moist.

			if (bitRead(Sys::statuses, Sys::STATUS_HEATING)) {
				/// Moist & heater is off.
				/// Heater safety timer.
				// if (ops.heaterTimeout.check(ops.currentTime)) {
				if (Util::getTimer(Sys::TIMER_HEATER_TIMEOUT)) {
					// If the heater has been on too long, turn it off and start cooldown.
					heaterOff();
					// ops.heaterCooldown.reset();
					Util::resetTimer(Sys::TIMER_HEATER_COOLDOWN);
					bitClear(Sys::statuses, Sys::STATUS_ACTIVE);
					return;
				}

				/// Box up to temperature.
				if (Sys::sensTemp >= Filaments::activeFilament.temperature) {
					// If the box is up to temperature: turn the heater off; turn the fan off;
					// set status to idle; get out of here.
					heaterOff();
					fanOff();
					bitClear(Sys::statuses, Sys::STATUS_ACTIVE);
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
			Util::resetTimer(Sys::TIMER_INPUT_POLLING_IDLE);
			bitClear(Sys::statuses, Sys::STATUS_ACTIVE);
		}
	}

	void idle() {
		if (bitRead(
				Sys::statuses,
				Sys::STATUS_ERROR
			) /*|| !ops.heaterCooldown.get(ops.currentTime)*/) {
			// Get out.
			return;
		}
		if (Sys::sensHumid > Filaments::activeFilament.humidity) {
			/// Moist.
			fanOnHigh();
			heaterOn();
			bitSet(Sys::statuses, Sys::STATUS_ACTIVE);
		} else {
		}
	}

	void heaterDuty() {
		if (bitRead(Sys::statuses, Sys::STATUS_HEATING)
			&& Sys::thermTemp >= Filaments::activeFilament.temperature + Sys::tempDelta) {
			// If thermistor temp is more than [delta] degrees above the sensor temperature,
			// turn it off.
			heaterOff();
		} else if (!bitRead(Sys::statuses, Sys::STATUS_HEATING)
				   && Sys::thermTemp < Filaments::activeFilament.temperature + Sys::tempDelta
				   && bitRead(Sys::statuses, Sys::STATUS_FANNING)) {
			heaterOn();
		}
	}

	void heaterOn() {
		digitalWrite(Pins::pHeater, LOW);
		digitalWrite(Pins::pLedHeat, LOW);
		// ops.inputPollingActive.reset();
		Util::resetTimer(Sys::TIMER_INPUT_POLLING_ACTIVE);
		bitClear(Sys::statuses, Sys::STATUS_HEATING);
	}

	void heaterOff() {
		digitalWrite(Pins::pHeater, HIGH);
		digitalWrite(Pins::pLedHeat, HIGH);
		bitClear(Sys::statuses, Sys::STATUS_HEATING);
	}

	void fanOnLow() {
		// TODO scale to 255
		analogWrite(Pins::pFan, 10);
		bitClear(Sys::statuses, Sys::STATUS_FANNING);
	}

	void fanOnHigh() {
		// TODO scale to 255
		analogWrite(Pins::pFan, 50);
		bitClear(Sys::statuses, Sys::STATUS_FANNING);
	}

	void fanOff() {
		analogWrite(Pins::pFan, 0);
		bitClear(Sys::statuses, Sys::STATUS_FANNING);
	}
}
