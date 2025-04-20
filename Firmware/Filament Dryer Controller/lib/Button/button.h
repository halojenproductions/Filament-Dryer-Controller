#include "filaments.h"
#include "operations.h"
#include <Arduino.h>

#ifndef BUTTON_H
#define BUTTON_H

// Declare external dependencies
extern Ops& ops;
extern Filaments& filaments;
extern const byte pButt;
extern uint32_t currentTime;

// Interrupt stuff.
bool interrupted();
void interruptHandler();
void interruptAnalyser();

// Other buttony stuff.
void buttonHeld();
void buttonClicked();

#endif
