#include "system.h"

namespace Sys {
	byte statuses = 0;
	byte commands = 0;

	// Global time.
	uint32_t currentTime		= millis();
	// Exhaust temperature delta.
	constexpr uint8_t tempDelta = 5;	// Degrees Celsius.

	// Fan speeds.
	constexpr uint8_t FAN_SPEED_LOW	 = 10 * (255 / 100);	// 10% duty cycle.
	constexpr uint8_t FAN_SPEED_HIGH = 50 * (255 / 100);	// 100% duty cycle.

	uint8_t sensHumid = 0;
	uint8_t sensTemp  = 99;
	uint8_t thermTemp = 99;

	Timer activeInputPolling(INPUT_POLL_ACTIVE_INTERVAL);
	Timer idleInputPolling(INPUT_POLL_IDLE_INTERVAL);
	Timer screenTimeout(SCREEN_TIMEOUT_INTERVAL);
	Timer selectionTimeout(SELECTION_TIMEOUT_INTERVAL);
	Timer buttonHoldTimeout(BUTTON_HOLD_TIMEOUT_INTERVAL);

}
