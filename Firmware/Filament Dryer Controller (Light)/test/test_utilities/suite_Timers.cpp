#include "test_utilities.h"

namespace suite_util_timers {
	using namespace Sys;
	using namespace Util;

	void timers_GetCheckReset();

	void suite_Timers() {
		RUN_TEST(timers_GetCheckReset);
	}

	// Tests.
	void timers_GetCheckReset(void) {
		Timer sut(100UL);
		Sys::currentTime = millis();

		// Within interval.
		TEST_ASSERT_FALSE(Util::getTimer(sut));
		TEST_ASSERT_FALSE(Util::checkTimer(sut));

		// Beyond interval.
		Sys::currentTime += 110;
		TEST_ASSERT_TRUE(Util::getTimer(sut));
		TEST_ASSERT_TRUE(Util::checkTimer(sut));

		// Was reset when checked beyond interval.
		TEST_ASSERT_FALSE(Util::checkTimer(sut));
	}
}
