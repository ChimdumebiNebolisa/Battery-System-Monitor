/**
 * battery.h - Battery data model and simulation for Battery System Monitor.
 * Defines battery state, safe operating thresholds, and update behavior.
 */

#ifndef BATTERY_H
#define BATTERY_H

/* ---------------------------------------------------------------------------
 * Safe operating thresholds (configuration values for later safety logic).
 * --------------------------------------------------------------------------- */
#define BATTERY_VOLTAGE_MIN_V    2.8f   /* Minimum safe cell voltage (V) */
#define BATTERY_VOLTAGE_MAX_V    4.2f   /* Maximum safe cell voltage (V) */
#define BATTERY_TEMP_MIN_C      -10.0f  /* Minimum safe temperature (°C) */
#define BATTERY_TEMP_MAX_C       55.0f  /* Maximum safe temperature (°C) */
#define BATTERY_CURRENT_MAX_A    10.0f  /* Maximum safe current magnitude (A) */
#define BATTERY_SOC_MIN_PERCENT   0.0f  /* Minimum state of charge (%) */
#define BATTERY_SOC_MAX_PERCENT 100.0f  /* Maximum state of charge (%) */

/* ---------------------------------------------------------------------------
 * Battery state: values that define current condition.
 * --------------------------------------------------------------------------- */
typedef struct BatteryState {
	float voltage_v;       /* Terminal voltage (V) */
	float temperature_c;   /* Temperature (°C) */
	float charge_level;    /* State of charge, 0.0 to 100.0 (%) */
	float current_a;       /* Current: positive = charging, negative = discharging (A) */
} BatteryState;

/* ---------------------------------------------------------------------------
 * Initialization and inspection.
 * --------------------------------------------------------------------------- */

/**
 * Set battery state to default starting values.
 */
void battery_init(BatteryState *b);

/**
 * Print current battery values to stdout in a readable format.
 */
void battery_print(const BatteryState *b);

/* ---------------------------------------------------------------------------
 * Simulation: update battery state over time.
 * --------------------------------------------------------------------------- */

/**
 * Modes for the simulation step (charging vs discharging).
 */
typedef enum {
	BATTERY_MODE_IDLE,
	BATTERY_MODE_CHARGING,
	BATTERY_MODE_DISCHARGING
} BatteryMode;

/**
 * Advance battery state by one simulation step.
 * Behavior depends on mode: charging increases charge/voltage, discharging decreases them.
 * Values are clamped to physically plausible ranges.
 */
void battery_step(BatteryState *b, BatteryMode mode, float dt_sec);

#endif /* BATTERY_H */
