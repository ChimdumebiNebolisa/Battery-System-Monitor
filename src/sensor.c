/**
 * sensor.c - Simulated sensor implementation.
 * Returns values from the battery state as if from hardware sensors.
 */

#include "sensor.h"

float sensor_read_voltage(const BatteryState *battery) {
	if (!battery) return 0.0f;
	return battery->voltage_v;
}

float sensor_read_temperature(const BatteryState *battery) {
	if (!battery) return 0.0f;
	return battery->temperature_c;
}

float sensor_read_current(const BatteryState *battery) {
	if (!battery) return 0.0f;
	return battery->current_a;
}
