#include "filaments.h"
#include "operations.h"
#include <Arduino.h>

#ifndef BUTTON_H
#define BUTTON_H

// Declare external dependencies
extern Ops& ops;
extern Filaments& filaments;
extern const int pButt;
extern uint32_t currentTime;

extern volatile byte interrupt;

// Function declarations
bool interrupted();
void handleButtonInterrupt();
void buttonInterruption();
void buttonHeld();
void buttonClicked();

#endif
