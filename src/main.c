/**
 * main.c - Battery System Monitor entry point.
 * Monitoring loop: read sensors → safety check → state update → effective mode → battery step → log/print.
 * Runs normal and failure scenarios (M3.3, M6).
 */

#include "battery.h"
#include "sensor.h"
#include "safety.h"
#include "state.h"
#include "log.h"
#include <stdio.h>

static const float DT_SEC = 1.0f;

static RequestedMode requested_mode_for_tick(int tick, int phase_ticks) {
	if (tick <= phase_ticks) return REQUEST_CHARGE;
	if (tick <= 2 * phase_ticks) return REQUEST_DISCHARGE;
	return REQUEST_IDLE;
}

static void run_monitoring_loop(BatteryState *bat, int total_ticks, int phase_ticks,
                                int *out_fault_seen, int *out_warning_seen) {
	SystemState state = SYSTEM_STATE_IDLE;
	*out_fault_seen = 0;
	*out_warning_seen = 0;

	for (int tick = 1; tick <= total_ticks; tick++) {
		/* 1. Read sensors (before step so we check current state). */
		float voltage_v  = sensor_read_voltage(bat);
		float temp_c     = sensor_read_temperature(bat);
		float current_a  = sensor_read_current(bat);

		/* 2. Safety check. */
		SafetyResult safety;
		safety_check(voltage_v, temp_c, current_a, &safety);

		RequestedMode requested = requested_mode_for_tick(tick, phase_ticks);
		SystemState prev = state;
		state = state_update(state, requested, &safety);

		/* 3. Log state transition. */
		if (state != prev) {
			char buf[LOG_MSG_MAX];
			snprintf(buf, sizeof(buf), "%s -> %s", state_display(prev), state_display(state));
			log_event(tick, LOG_STATE_TRANSITION, buf);
		}
		if (safety.over_temp) {
			log_event(tick, LOG_SAFETY_SHUTDOWN, "over-temperature");
			log_event(tick, LOG_THRESHOLD_VIOLATION, "temperature exceeds limit");
			*out_fault_seen = 1;
		}
		if (safety.over_voltage) {
			log_event(tick, LOG_THRESHOLD_VIOLATION, "voltage exceeds limit");
			*out_warning_seen = 1;
		}
		if (safety.over_current) {
			log_event(tick, LOG_THRESHOLD_VIOLATION, "current exceeds limit");
			*out_warning_seen = 1;
		}
		if (state == SYSTEM_STATE_CHARGING && prev != SYSTEM_STATE_CHARGING)
			log_event(tick, LOG_CHARGE_CYCLE, "charging started");
		if (state == SYSTEM_STATE_DISCHARGING && prev != SYSTEM_STATE_DISCHARGING)
			log_event(tick, LOG_DISCHARGE_CYCLE, "discharge started");

		/* 4. Effective mode and battery step. */
		BatteryMode effective = state_effective_battery_mode(state, requested, &safety);
		battery_step(bat, effective, DT_SEC);

		/* 5. Print step (readable; show warnings/faults). */
		const char *state_str = state_display(state);
		printf("  [tick %3d] state=%-10s V=%.2f T=%.1f I=%.2f",
		       tick, state_str, sensor_read_voltage(bat), sensor_read_temperature(bat), sensor_read_current(bat));
		if (state == SYSTEM_STATE_FAULT) printf("  FAULT");
		else if (state == SYSTEM_STATE_WARNING) printf("  WARNING");
		printf("\n");
	}
}

static void scenario_normal(void) {
	printf("\n--- Scenario: Normal operation (charge then discharge then idle) ---\n");
	log_clear();
	BatteryState bat;
	battery_init(&bat);

	int fault = 0, warning = 0;
	run_monitoring_loop(&bat, 18, 6, &fault, &warning);

	printf("  Result: fault=%d warning=%d (expect 0,0)\n", fault, warning);
	printf("  Final state: ");
	battery_print(&bat);
}

static void scenario_over_voltage(void) {
	printf("\n--- Scenario: Over-voltage (charging stopped) ---\n");
	log_clear();
	BatteryState bat;
	battery_init(&bat);
	bat.voltage_v = 4.25f;  /* Above BATTERY_VOLTAGE_MAX_V (4.2) */
	bat.charge_level = 95.0f;

	int fault = 0, warning = 0;
	run_monitoring_loop(&bat, 3, 1, &fault, &warning);

	printf("  Result: fault=%d warning=%d (expect 0,1)\n", fault, warning);
	printf("  Charging should have been stopped; state should be warning.\n");
}

static void scenario_over_temp(void) {
	printf("\n--- Scenario: Over-temperature (shutdown) ---\n");
	log_clear();
	BatteryState bat;
	battery_init(&bat);
	bat.temperature_c = 60.0f;  /* Above BATTERY_TEMP_MAX_C (55) */

	int fault = 0, warning = 0;
	run_monitoring_loop(&bat, 2, 1, &fault, &warning);

	printf("  Result: fault=%d warning=%d (expect 1,0)\n", fault, warning);
	printf("  System should have entered fault state.\n");
}

static void scenario_over_current(void) {
	printf("\n--- Scenario: Over-current (warning) ---\n");
	log_clear();
	BatteryState bat;
	battery_init(&bat);
	bat.current_a = 12.0f;  /* Above BATTERY_CURRENT_MAX_A (10) */

	int fault = 0, warning = 0;
	run_monitoring_loop(&bat, 2, 1, &fault, &warning);

	printf("  Result: fault=%d warning=%d (expect 0,1)\n", fault, warning);
	printf("  Warning should be raised for unsafe current.\n");
}

int main(void) {
	printf("Battery System Monitor\n");
	printf("Initial battery state:\n");
	BatteryState bat;
	battery_init(&bat);
	battery_print(&bat);

	scenario_normal();
	scenario_over_voltage();
	scenario_over_temp();
	scenario_over_current();

	printf("\n--- Event log (normal run for log sample) ---\n");
	log_clear();
	battery_init(&bat);
	int fault_dummy, warning_dummy;
	run_monitoring_loop(&bat, 12, 4, &fault_dummy, &warning_dummy);
	printf("\nLogged events:\n");
	log_print_all();
	printf("\nDone.\n");
	return 0;
}
