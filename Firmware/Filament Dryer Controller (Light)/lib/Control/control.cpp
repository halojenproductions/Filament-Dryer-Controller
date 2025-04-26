#include "control.h"

namespace Control {
	using namespace Util;

	Timer activeTimeout(Sys::ACTIVE_TIMEOUT_INTERVAL);
	Timer activeCooldown(Sys::ACTIVE_COOLDOWN_INTERVAL);
	Timer heatingTimeout(Sys::HEATING_TIMEOUT_INTERVAL);
	Timer heatingCooldown(Sys::HEATING_COOLDOWN_TIME_INTERVAL);
	Timer heatDutyTimeout(Sys::HEAT_DUTY_TIMEOUT_INTERVAL);

	void active() {
		// Serial.println("Active");
		if (Sys::sensHumid > Filaments::activeFilament.humidity) {
			/// Moist.

			if (checkTimer(activeTimeout)) {
				// Maybe desiccant needs replacing.
				// TODO set error state.
				bitSet(Sys::statuses, Sys::STATUS_ERROR);
				heaterOff();
				fanLow();
				bitClear(Sys::statuses, Sys::STATUS_HEATING);
				bitClear(Sys::statuses, Sys::STATUS_ACTIVE);
				Serial.println(F("Active timeout."));
				return;
			}

			if (bitRead(Sys::statuses, Sys::STATUS_HEATING)) {
				/// Moist & heater is on.
				/// Heater safety timer.
				if (checkTimer(heatingTimeout)) {
					// We've been heating too long.
					// Stop heating for a while but leave the fan on.
					heaterOff();
					resetTimer(heatingCooldown);
					bitClear(Sys::statuses, Sys::STATUS_ACTIVE);
					return;
				}

				/// Box up to temperature.
				if (Sys::sensTemp >= Filaments::activeFilament.temperature) {
					// If the box is up to temperature: turn the heater off; turn the fan off;
					// set status to idle; get out of here.
					heaterOff();
					fanOff();
					bitClear(Sys::statuses, Sys::STATUS_HEATING);
					return;
				}
			}

			/// Heater duty.
			heaterDuty();

		} else {
			/// Dry.

			heaterOff();
			fanOff();
			resetTimer(Sys::idleInputPolling);
			bitClear(Sys::statuses, Sys::STATUS_ACTIVE);
		}
	}

	void idle() {
		if (bitRead(Sys::statuses, Sys::STATUS_ERROR) || !checkTimer(activeCooldown)) {
			// Get out.
			return;
		}
		if (Sys::sensHumid > Filaments::activeFilament.humidity) {
			/// Moist.
			fanHigh();
			resetTimer(activeTimeout);
			bitSet(Sys::statuses, Sys::STATUS_ACTIVE);
		} else {
			// TODO
		}
	}

	void heaterDuty() {
		if (getTimer(heatDutyTimeout)) {
			// Element should not be on that long.
			// Either the element is broken or the thermistor has failed. Terminal error.
			// TODO set error state.
			bitSet(Sys::statuses, Sys::STATUS_ERROR);
			heaterOff();
			Serial.println(F("Heater duty timeout."));
			return;
		}

		if (!bitRead(Sys::statuses, Sys::STATUS_HEATING)) {
			// Not sure why we'd get here, but if we do.. well.. turn the heater off.
			heaterOff();
		}

		if (bitRead(Sys::statuses, Sys::STATUS_HEATING)
			&& bitRead(Sys::statuses, Sys::STATUS_HEAT_DUTY)
			&& Sys::thermTemp >= Filaments::activeFilament.temperature + Sys::tempDelta) {
			// If thermistor temp is more than [delta] degrees above the sensor temperature,
			// cycle it off.
			heaterOff();
		} else if (bitRead(Sys::statuses, Sys::STATUS_HEATING)
				   && Sys::thermTemp < Filaments::activeFilament.temperature + Sys::tempDelta
				   && !bitRead(Sys::statuses, Sys::STATUS_HEAT_DUTY)) {

			resetTimer(heatDutyTimeout);
			heaterOn();
		}
	}

	void heaterOn() {
		fanHigh();	  // The fan should already be on, this is just for safety.
		bitSet(Sys::statuses, Sys::STATUS_HEAT_DUTY);
		digitalWrite(Pins::pHeater, LOW);
		digitalWrite(Pins::pLedHeat, HIGH);
	}

	void heaterOff() {
		digitalWrite(Pins::pHeater, HIGH);
		digitalWrite(Pins::pLedHeat, LOW);
		bitClear(Sys::statuses, Sys::STATUS_HEAT_DUTY);
	}

	void fanHigh() {
		// TODO scale to 255
		analogWrite(Pins::pFan, Sys::FAN_SPEED_HIGH);
	}

	void fanLow() {
		// TODO scale to 255
		analogWrite(Pins::pFan, Sys::FAN_SPEED_LOW);
	}

	void fanOff() {
		analogWrite(Pins::pFan, 0);
	}
}
