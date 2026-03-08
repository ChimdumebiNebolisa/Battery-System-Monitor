/**
 * main.c - Entry point for Battery System Monitor (Milestone 1).
 * Runs a minimal simulation: init battery, run several steps, print state.
 */

#include "battery.h"
#include <stdio.h>

int main(void) {
	BatteryState bat;
	battery_init(&bat);

	printf("Battery System Monitor - Milestone 1\n");
	printf("Initial state:\n");
	battery_print(&bat);

	printf("\nSimulation: 5 steps charging, 5 steps discharging, 2 steps idle.\n");
	const float dt = 1.0f;

	for (int step = 0; step < 5; step++) {
		battery_step(&bat, BATTERY_MODE_CHARGING, dt);
		printf("  step %d (charging)  ", step + 1);
		battery_print(&bat);
	}
	for (int step = 0; step < 5; step++) {
		battery_step(&bat, BATTERY_MODE_DISCHARGING, dt);
		printf("  step %d (discharging) ", step + 6);
		battery_print(&bat);
	}
	for (int step = 0; step < 2; step++) {
		battery_step(&bat, BATTERY_MODE_IDLE, dt);
		printf("  step %d (idle) ", step + 11);
		battery_print(&bat);
	}

	printf("\nDone.\n");
	return 0;
}
