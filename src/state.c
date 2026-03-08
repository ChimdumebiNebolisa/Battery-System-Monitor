/**
 * state.c - State transition rules and effective mode.
 */

#include "state.h"

const char *state_display(SystemState s) {
	switch (s) {
	case SYSTEM_STATE_IDLE:        return "idle";
	case SYSTEM_STATE_CHARGING:    return "charging";
	case SYSTEM_STATE_DISCHARGING: return "discharging";
	case SYSTEM_STATE_WARNING:     return "warning";
	case SYSTEM_STATE_FAULT:      return "fault";
	default:                       return "?";
	}
}

SystemState state_update(SystemState current, RequestedMode requested, const SafetyResult *safety) {
	if (!safety) return current;

	/* Fault overrides everything: dangerous temperature → shutdown. */
	if (safety_has_fault(safety))
		return SYSTEM_STATE_FAULT;

	/* Warning: over-voltage or over-current. State becomes WARNING. */
	if (safety_has_warning(safety))
		return SYSTEM_STATE_WARNING;

	/* No fault, no warning: normal operation from requested mode. */
	switch (requested) {
	case REQUEST_CHARGE:    return SYSTEM_STATE_CHARGING;
	case REQUEST_DISCHARGE: return SYSTEM_STATE_DISCHARGING;
	case REQUEST_IDLE:      return SYSTEM_STATE_IDLE;
	default:                return SYSTEM_STATE_IDLE;
	}
}

BatteryMode state_effective_battery_mode(SystemState state, RequestedMode requested, const SafetyResult *safety) {
	if (state == SYSTEM_STATE_FAULT)
		return BATTERY_MODE_IDLE;

	if (state == SYSTEM_STATE_WARNING) {
		/* Stop charging on over-voltage; on over-current raise warning (no charge/discharge for safety). */
		if (safety && safety->over_voltage)
			return BATTERY_MODE_IDLE;
		if (safety && safety->over_current)
			return BATTERY_MODE_IDLE;
		if (safety && safety->over_temp)
			return BATTERY_MODE_IDLE;
		return BATTERY_MODE_IDLE; /* Any warning → idle until clear */
	}

	switch (requested) {
	case REQUEST_CHARGE:    return BATTERY_MODE_CHARGING;
	case REQUEST_DISCHARGE: return BATTERY_MODE_DISCHARGING;
	default:                return BATTERY_MODE_IDLE;
	}
}
