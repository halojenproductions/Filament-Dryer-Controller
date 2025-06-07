#include "test_control.h"

void setUp(void) {}

void tearDown(void) {}

void setup() {
	delay(200);
	UNITY_BEGIN();

	suite_control_active::suite_Active();
	suite_control_errors::suite_Errors();
	// suite_control_error::suite_Error();

	UNITY_END();
}

void loop() {}
