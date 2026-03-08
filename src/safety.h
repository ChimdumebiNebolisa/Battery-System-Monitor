/**
 * safety.h - Safety threshold checks and protective responses.
 * Uses threshold constants from battery.h; keeps safety logic obvious and separate.
 */

#ifndef SAFETY_H
#define SAFETY_H

/* ---------------------------------------------------------------------------
 * Result of a safety check (from current sensor readings).
 * Non-zero = condition detected; responses are defined in safety.c / monitor.
 * --------------------------------------------------------------------------- */
typedef struct SafetyResult {
	int over_voltage;   /* 1 if voltage exceeds safe max */
	int over_temp;      /* 1 if temperature exceeds safe max (triggers shutdown) */
	int over_current;   /* 1 if |current| exceeds safe max (triggers warning) */
} SafetyResult;

/**
 * Evaluate sensor readings against safe operating thresholds.
 * Thresholds are from battery.h (BATTERY_VOLTAGE_MAX_V, BATTERY_TEMP_MAX_C, BATTERY_CURRENT_MAX_A).
 */
void safety_check(float voltage_v, float temp_c, float current_a, SafetyResult *out);

/**
 * Returns 1 if any fault condition (e.g. over_temp → shutdown) is set.
 */
int safety_has_fault(const SafetyResult *r);

/**
 * Returns 1 if any warning condition (over_voltage, over_current) is set.
 */
int safety_has_warning(const SafetyResult *r);

#endif /* SAFETY_H */
