/**
 * battery.c - Battery data model and basic simulation implementation.
 */

#include "battery.h"
#include <stdio.h>

/* Default starting values for a partially charged battery at rest. */
#define DEFAULT_VOLTAGE_V    3.7f
#define DEFAULT_TEMP_C       25.0f
#define DEFAULT_CHARGE_PCT   50.0f
#define DEFAULT_CURRENT_A    0.0f

/* Nominal voltage range for mapping charge level to voltage (simple linear model). */
#define V_AT_0_PCT   BATTERY_VOLTAGE_MIN_V
#define V_AT_100_PCT BATTERY_VOLTAGE_MAX_V

/* Simple rate constants for simulation (per second). */
#define CHARGE_RATE_PER_A    2.0f   /* % SOC gain per A per second (scaled) */
#define DISCHARGE_RATE_PER_A 2.0f   /* % SOC loss per A per second (scaled) */
#define TEMP_RISE_PER_W      0.02f  /* °C rise per watt (simplified thermal) */

void battery_init(BatteryState *b) {
	if (!b) return;
	b->voltage_v     = DEFAULT_VOLTAGE_V;
	b->temperature_c = DEFAULT_TEMP_C;
	b->charge_level  = DEFAULT_CHARGE_PCT;
	b->current_a     = DEFAULT_CURRENT_A;
}

void battery_print(const BatteryState *b) {
	if (!b) return;
	printf("  voltage=%.2f V  temp=%.1f °C  SOC=%.1f%%  current=%.2f A\n",
	       b->voltage_v, b->temperature_c, b->charge_level, b->current_a);
}

/**
 * Clamp a value to [lo, hi].
 */
static float clampf(float x, float lo, float hi) {
	if (x < lo) return lo;
	if (x > hi) return hi;
	return x;
}

void battery_step(BatteryState *b, BatteryMode mode, float dt_sec) {
	if (!b || dt_sec <= 0.0f) return;

	switch (mode) {
	case BATTERY_MODE_IDLE:
		b->current_a = 0.0f;
		/* Small self-discharge / relaxation: voltage and temp drift slightly. */
		b->charge_level = clampf(b->charge_level - 0.001f * dt_sec,
		                        BATTERY_SOC_MIN_PERCENT, BATTERY_SOC_MAX_PERCENT);
		b->voltage_v = V_AT_0_PCT + (b->charge_level / 100.0f) * (V_AT_100_PCT - V_AT_0_PCT);
		b->temperature_c = clampf(b->temperature_c - 0.01f * dt_sec,
		                          BATTERY_TEMP_MIN_C, BATTERY_TEMP_MAX_C);
		break;

	case BATTERY_MODE_CHARGING: {
		float i = 2.0f; /* Simulated charging current (A). */
		b->current_a = i;
		b->charge_level = clampf(b->charge_level + CHARGE_RATE_PER_A * i * dt_sec * 0.1f,
		                         BATTERY_SOC_MIN_PERCENT, BATTERY_SOC_MAX_PERCENT);
		b->voltage_v = V_AT_0_PCT + (b->charge_level / 100.0f) * (V_AT_100_PCT - V_AT_0_PCT);
		b->voltage_v = clampf(b->voltage_v, V_AT_0_PCT, V_AT_100_PCT);
		/* Charging adds some heat. */
		float power_w = b->voltage_v * i;
		b->temperature_c = clampf(b->temperature_c + TEMP_RISE_PER_W * power_w * dt_sec * 0.1f,
		                          BATTERY_TEMP_MIN_C, BATTERY_TEMP_MAX_C);
		break;
	}

	case BATTERY_MODE_DISCHARGING: {
		float i = -3.0f; /* Simulated discharge current (A), negative. */
		b->current_a = i;
		b->charge_level = clampf(b->charge_level + DISCHARGE_RATE_PER_A * (-i) * dt_sec * 0.1f,
		                         BATTERY_SOC_MIN_PERCENT, BATTERY_SOC_MAX_PERCENT);
		b->voltage_v = V_AT_0_PCT + (b->charge_level / 100.0f) * (V_AT_100_PCT - V_AT_0_PCT);
		b->voltage_v = clampf(b->voltage_v, V_AT_0_PCT, V_AT_100_PCT);
		float power_w = b->voltage_v * (-i);
		b->temperature_c = clampf(b->temperature_c + TEMP_RISE_PER_W * power_w * dt_sec * 0.1f,
		                          BATTERY_TEMP_MIN_C, BATTERY_TEMP_MAX_C);
		break;
	}
	}
}
