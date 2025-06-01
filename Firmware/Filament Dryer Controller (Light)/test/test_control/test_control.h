#include "control.h"
#include "system.h"
#include "utilities.h"
#include <Arduino.h>
#include <unity.h>

#ifndef TEST_CONTROL_H
#define TEST_CONTROL_H

constexpr byte mask = 0b11111111;

namespace suite_control_active {
	void suite_Active();
}

// namespace suite_control_humid {
// 	void suite_Humid();
// }

// namespace suite_control_error {
// 	void suite_Error();
// }

void setUp(void);
void tearDown(void);

void setup();

void loop();

namespace test_control_helpers {}

#endif
