#include "test_control.h"

namespace suite_control_active {
	using namespace Sys;
	using namespace Util;
	using namespace Control;

	void test_active_timeout();
	void test_active_heating_timeout();
	void test_active_heater_duty();
	void test_active_dry_condition();
	void setup();

	void suite_Active() {
		RUN_TEST(test_active_timeout);
		RUN_TEST(test_active_heating_timeout);
		RUN_TEST(test_active_heater_duty);
		RUN_TEST(test_active_dry_condition);
	}

	void test_active_timeout() {
		// Arrange.
		setup();
		setStatus(Status::Moist);

		// Advance time past the timeout interval
		currentTime = ACTIVE_TIMEOUT_INTERVAL + 1;

		// Act.
		active();

		// Assert.
		TEST_ASSERT_TRUE_MESSAGE(
			getError(Error::ActiveTimeout),
			"Active timeout error should be set"
		);
		TEST_ASSERT_FALSE_MESSAGE(getStatus(Status::Heating), "Heating status should be cleared");
		TEST_ASSERT_FALSE_MESSAGE(getStatus(Status::Active), "Active status should be cleared");
	}

	void test_active_heating_timeout() {
		// Arrange.
		setup();
		setStatus(Status::Moist);
		setStatus(Status::Heating);

		// Advance time past the heating timeout interval.
		currentTime = HEATING_TIMEOUT_INTERVAL + 1;

		// Act.
		active();

		// Assert.
		TEST_ASSERT_FALSE_MESSAGE(getStatus(Status::Heating), "Heating status should be cleared");
		TEST_ASSERT_FALSE_MESSAGE(getStatus(Status::Active), "Active status should be cleared");
	}

	void test_active_heater_duty() {
		// Arrange.
		setup();
		setStatus(Status::Moist);
		setStatus(Status::Heating);
		sensTemp  = 20;
		thermTemp = 50;

		// Act.
		active();

		// Assert.
		TEST_ASSERT_TRUE_MESSAGE(getStatus(Status::HeatDuty), "Heating element should be on");

		// Alter.
		thermTemp += TEMP_DELTA + 1;	// Simulate thermistor temperature above threshold.
		// Suck it, rules. I envented a new term that allows me to do multiple acts and assertions
		// in one block and still look like i know what i'm doing.

		// Act.
		active();

		// Assert.
		TEST_ASSERT_FALSE_MESSAGE(getStatus(Status::HeatDuty), "Heating element should be off");
	}

	void test_active_dry_condition() {
		// Arrange.
		setup();
		clearStatus(Status::Moist);
		setStatus(Status::Active);

		// Act.
		active();

		// Assert.
		TEST_ASSERT_FALSE_MESSAGE(
			getStatus(Status::Active),
			"Active status should be cleared when dry"
		);
	}

	void setup() {
		// Initialize state
		statuses	= 0;
		errors		= 0;
		currentTime = 0;
		// System timers.
		activeInputPolling.reset(currentTime);
		idleInputPolling.reset(currentTime);
		screenTimeout.reset(currentTime);
		selectionTimeout.reset(currentTime);
		buttonHoldTimeout.reset(currentTime);
		// Control timers.
		activeTimeout.reset(currentTime);
		activeCooldown.reset(currentTime);
		heatingTimeout.reset(currentTime);
		heatDutyTimeout.reset(currentTime);
		heatingCooldown.reset(currentTime);
		// Filament profile.
		Filaments::activeFilament.humidity	  = 50;
		Filaments::activeFilament.temperature = 50;
	}
}
