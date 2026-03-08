/**
 * state.h - System operating states and transition rules.
 * States: idle, charging, discharging, warning, fault (shutdown).
 */

#ifndef STATE_H
#define STATE_H

#include "battery.h"
#include "safety.h"

typedef enum {
	SYSTEM_STATE_IDLE,
	SYSTEM_STATE_CHARGING,
	SYSTEM_STATE_DISCHARGING,
	SYSTEM_STATE_WARNING,
	SYSTEM_STATE_FAULT
} SystemState;

/* Requested mode from application (e.g. "user wants to charge"). */
typedef enum {
	REQUEST_IDLE,
	REQUEST_CHARGE,
	REQUEST_DISCHARGE
} RequestedMode;

/**
 * Return a readable string for the current state (for display/logging).
 */
const char *state_display(SystemState s);

/**
 * Update system state based on current state, requested mode, and safety result.
 * Fault (over_temp) overrides everything. Warning (over_voltage/over_current) forces
 * protective response (e.g. stop charging) and may set state to WARNING.
 * Normal states (idle/charging/discharging) when no fault and conditions allow.
 */
SystemState state_update(SystemState current, RequestedMode requested, const SafetyResult *safety);

/**
 * Effective battery mode for this step: what we actually do after safety and state.
 * e.g. If state is FAULT or we must stop charging due to over_voltage, returns IDLE.
 */
BatteryMode state_effective_battery_mode(SystemState state, RequestedMode requested, const SafetyResult *safety);

#endif /* STATE_H */
