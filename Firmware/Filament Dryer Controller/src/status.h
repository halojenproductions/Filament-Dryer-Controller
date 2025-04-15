#ifndef STATUS_H
#define STATUS_H

#include <stdint.h>

class Status {
  public:
	enum Flags {
		Ok	   = (1 << 0),	  // 0b00000001
		Error  = (1 << 1),	  // 0b00000001
		Screen = (1 << 2),	  // 0b00000010
		Heat   = (1 << 3),	  // 0b00000100
		Fan	   = (1 << 4),	  // 0b00001000
	};

	void set(Flags flag);
	void clear(Flags flag);
	void toggle(Flags flag);
	bool isSet(Flags flag) const;
	unsigned char getRaw() const;

  private:
	unsigned char status = 0;
};

#endif	  // STATUS_H
