#ifndef THERMISTOR_H
#define THERMISTOR_H

class Thermistor {
	public:

	Thermistor();
	Thermistor(int value);
	operator int() const;
	Thermistor& operator=(int value);

	private:

	int temp_;
	static int adcToCelsius(int adc_value);
};

#endif
