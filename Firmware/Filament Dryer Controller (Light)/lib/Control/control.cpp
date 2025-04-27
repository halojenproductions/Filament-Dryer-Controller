#include "control.h"

namespace Control {
	using namespace Sys;
	using namespace Util;

	Timer activeTimeout(ACTIVE_TIMEOUT_INTERVAL);
	Timer activeCooldown(ACTIVE_COOLDOWN_INTERVAL);
	Timer heatingTimeout(HEATING_TIMEOUT_INTERVAL);
	Timer heatingCooldown(HEATING_COOLDOWN_TIME_INTERVAL);
	Timer heatDutyTimeout(HEAT_DUTY_TIMEOUT_INTERVAL);

	void active() {
		// Serial.println("Active");
		if (sensHumid > Filaments::activeFilament.humidity) {
			/// Moist.

			if (checkTimer(activeTimeout)) {
				// Maybe desiccant needs replacing.
				// TODO set error state.
				setStatus(Status::Error);
				heaterOff();
				fanLow();
				clearStatus(Status::Heating);
				clearStatus(Status::Active);
				Serial.println(F("Active timeout."));
				return;
			}

			if (getStatus(Status::Heating)) {
				/// Moist & heater is on.
				/// Heater safety timer.
				if (checkTimer(heatingTimeout)) {
					// We've been heating too long.
					// Stop heating for a while but leave the fan on.
					heaterOff();
					resetTimer(heatingCooldown);
					clearStatus(Status::Active);
					return;
				}

				/// Box up to temperature.
				if (sensTemp >= Filaments::activeFilament.temperature) {
					// If the box is up to temperature: turn the heater off; turn the fan off;
					// set status to idle; get out of here.
					heaterOff();
					fanOff();
					clearStatus(Status::Heating);
					return;
				}
			}

			/// Heater duty.
			heaterDuty();

		} else {
			/// Dry.

			heaterOff();
			fanOff();
			resetTimer(idleInputPolling);
			clearStatus(Status::Active);
		}
	}

	void idle() {
		if (getStatus(Status::Error) || !checkTimer(activeCooldown)) {
			// Get out.
			return;
		}
		if (sensHumid > Filaments::activeFilament.humidity) {
			/// Moist.
			fanHigh();
			resetTimer(activeTimeout);
			setStatus(Status::Active);
		} else {
			// TODO
		}
	}

	void heaterDuty() {
		if (getTimer(heatDutyTimeout)) {
			// Element should not be on that long.
			// Either the element is broken or the thermistor has failed. Terminal error.
			// TODO set error state.
			setStatus(Status::Error);
			heaterOff();
			Serial.println(F("Heater duty timeout."));
			return;
		}

		if (!getStatus(Status::Heating)) {
			// Not sure why we'd get here, but if we do.. well.. turn the heater off.
			heaterOff();
		}

		if (getStatus(Status::Heating)
			&& getStatus(Status::HeatDuty)
			&& thermTemp >= Filaments::activeFilament.temperature + tempDelta) {
			// If thermistor temp is more than [delta] degrees above the sensor temperature,
			// cycle it off.
			heaterOff();
		} else if (getStatus(Status::Heating)
				   && thermTemp < Filaments::activeFilament.temperature + tempDelta
				   && !getStatus(Status::HeatDuty)) {

			resetTimer(heatDutyTimeout);
			heaterOn();
		}
	}

	void heaterOn() {
		fanHigh();	  // The fan should already be on, this is just for safety.
		setStatus(Status::HeatDuty);
		digitalWrite(Pins::pHeater, LOW);
		digitalWrite(Pins::pLedHeat, HIGH);
	}

	void heaterOff() {
		digitalWrite(Pins::pHeater, HIGH);
		digitalWrite(Pins::pLedHeat, LOW);
		clearStatus(Status::HeatDuty);
	}

	void fanHigh() {
		// TODO scale to 255
		analogWrite(Pins::pFan, FAN_SPEED_HIGH);
	}

	void fanLow() {
		// TODO scale to 255
		analogWrite(Pins::pFan, FAN_SPEED_LOW);
	}

	void fanOff() {
		analogWrite(Pins::pFan, 0);
	}
}
