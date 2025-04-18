#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <stdint.h>
#include "temperature.h"

class Ops {
	public:

	enum Status {
		Ok			= (1 << 0),	   // 0b00000001
		Error		= (1 << 1),	   // 0b00000010
		ScreenAwake = (1 << 2),	   // 0b00000100
		Heating		= (1 << 3),	   // 0b00001000
		Fanning		= (1 << 4),	   // 0b00010000
		ButtonDown	= (1 << 5),	   // 0b00100000
	};

	enum Command {
		Display = (1 << 0),
		// Error  = (1 << 1),
		// Screen = (1 << 2),
		Heat	= (1 << 3),
		Fan		= (1 << 4),
	};

	OutTemp outTemp = 0;	// Temperature in centigrade.
	int Humidity;
	int FanSpeed;

	// Status functions.
	void setStatus(Status status);
	void clearStatus(Status status);
	void toggleStatus(Status status);
	bool getStatus(Status status) const;
	unsigned char getStatusesRaw() const;

	// Command functions.
	void setCommand(Command command);
	void clearCommand(Command command);
	bool getCommand(Command command) const;
	unsigned char getCommandsRaw() const;

	// Other functions.
	void setInTemp(int temp) {
		inTemperature = temp;
	}

	int getInTemp() const {
		return inTemperature;
	}

	void setOutTemp(int temp) {
		outTemperature = temp;
	}

	int getOutTemp() const {
		return outTemperature;
	}

	private:

	unsigned char statuses = 0;
	unsigned char commands = 0;
	int inTemperature	   = 0;
	int outTemperature	   = 0;
	int humidity		   = 0;
};

#endif
