/**
 * safety.c - Threshold checks using battery.h constants.
 */

#include "safety.h"
#include "battery.h"

void safety_check(float voltage_v, float temp_c, float current_a, SafetyResult *out) {
	if (!out) return;
	out->over_voltage = (voltage_v > BATTERY_VOLTAGE_MAX_V) ? 1 : 0;
	out->over_temp    = (temp_c > BATTERY_TEMP_MAX_C) ? 1 : 0;
	{
		float abs_current = current_a < 0.0f ? -current_a : current_a;
		out->over_current = (abs_current > BATTERY_CURRENT_MAX_A) ? 1 : 0;
	}
}

int safety_has_fault(const SafetyResult *r) {
	return r && r->over_temp;
}

int safety_has_warning(const SafetyResult *r) {
	return r && (r->over_voltage || r->over_current);
}
