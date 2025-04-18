#ifndef TEMPERATURE_H
#define TEMPERATURE_H

class OutTemp {
	public:

	OutTemp();
	OutTemp(int value);
	operator int() const;
	OutTemp &operator=(int value);

	private:

	int temp_;
	static int adcToCelsius(int adc_value);
};

#endif
