#ifndef BUTTON_H
#define BUTTON_H

#include "operations.h"
#include <Arduino.h>

// Declare external dependencies
extern Ops ops;
extern const int pButt;
extern uint32_t currentTime;

// Function declarations
void handleButtonInterrupt();
void buttonInterruption();
void buttonHeld();

#endif
