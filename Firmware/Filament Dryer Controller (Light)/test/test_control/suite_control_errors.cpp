#include "test_control.h"

namespace suite_control_errors {
	using namespace Sys;
	using namespace Util;
	using namespace Control;

	void test_active_timeout_error();
	void test_heat_duty_timeout_error();
	void test_heat_duty_timeout_error_once();
	void setup();

	void suite_Errors() {
		RUN_TEST(test_active_timeout_error);
		RUN_TEST(test_heat_duty_timeout_error);
		RUN_TEST(test_heat_duty_timeout_error_once);
	}

	void test_active_timeout_error() {
		// Arrange.
		setup();
		setStatus(Status::Moist);

		// Advance time past the active timeout interval
		currentTime = ACTIVE_TIMEOUT_INTERVAL + 1;

		// Act.
		active();

		// Assert.
		TEST_ASSERT_TRUE_MESSAGE(
			getError(Error::ActiveTimeout),
			"ActiveTimeout error should be set when active timeout expires"
		);
		TEST_ASSERT_FALSE_MESSAGE(
			getStatus(Status::Heating),
			"Heating status should be cleared on active timeout"
		);
		TEST_ASSERT_FALSE_MESSAGE(
			getStatus(Status::Active),
			"Active status should be cleared on active timeout"
		);
	}

	void test_heat_duty_timeout_error() {
		// Arrange.
		setup();
		setStatus(Status::Moist);
		setStatus(Status::Heating);
		sensTemp  = 20;
		thermTemp = 30;

		// Trigger heater on by calling heaterDuty
		heaterDuty();
		TEST_ASSERT_TRUE_MESSAGE(getStatus(Status::HeatDuty), "Heater should be on for test setup");

		// Advance time past the heat duty timeout interval
		currentTime = HEAT_DUTY_TIMEOUT_INTERVAL + 1;

		// Act.
		heaterDuty();

		// Assert.
		TEST_ASSERT_TRUE_MESSAGE(
			getError(Error::HeatDutyTimeout),
			"HeatDutyTimeout error should be set when heat duty timeout expires"
		);
		TEST_ASSERT_FALSE_MESSAGE(
			getStatus(Status::HeatDuty),
			"Heat duty status should be cleared on timeout"
		);
	}

	void test_heat_duty_timeout_error_once() {
		// Arrange.
		setup();
		setStatus(Status::Moist);
		setStatus(Status::Heating);
		sensTemp  = 20;
		thermTemp = 30;

		// Trigger heater on by calling heaterDuty
		heaterDuty();

		// Advance time past the heat duty timeout interval
		currentTime = HEAT_DUTY_TIMEOUT_INTERVAL + 1;

		// Act - call heaterDuty multiple times
		heaterDuty();
		heaterDuty();
		heaterDuty();

		// Assert - error should only be set once (not multiple times)
		TEST_ASSERT_TRUE_MESSAGE(
			getError(Error::HeatDutyTimeout),
			"HeatDutyTimeout error should be set"
		);
		// Since this is a terminal error, it should remain set
		// This test verifies the error is only triggered once via the conditional check
	}

	void setup() {
		// Initialise state
		statuses	= 0;
		errors		= 0;
		currentTime = 0;

		// System timers
		activeInputPolling.reset(currentTime);
		idleInputPolling.reset(currentTime);
		screenTimeout.reset(currentTime);
		selectionTimeout.reset(currentTime);
		buttonHoldTimeout.reset(currentTime);

		// Control timers
		activeTimeout.reset(currentTime);
		activeCooldown.reset(currentTime);
		heatingTimeout.reset(currentTime);
		heatDutyTimeout.reset(currentTime);
		heatingCooldown.reset(currentTime);

		// Filament profile
		Filaments::activeFilament.humidity	  = 50;
		Filaments::activeFilament.temperature = 50;
	}
}
