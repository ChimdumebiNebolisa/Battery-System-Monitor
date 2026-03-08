/**
 * sensor.h - Simulated sensor interface for Battery System Monitor.
 * Provides a sensor-like API to read voltage, temperature, and current.
 * Kept separate from the battery model (monitoring reads through this layer).
 */

#ifndef SENSOR_H
#define SENSOR_H

#include "battery.h"

/**
 * Read simulated voltage (V) from the battery state.
 */
float sensor_read_voltage(const BatteryState *battery);

/**
 * Read simulated temperature (°C) from the battery state.
 */
float sensor_read_temperature(const BatteryState *battery);

/**
 * Read simulated current (A); positive = charging, negative = discharging.
 */
float sensor_read_current(const BatteryState *battery);

#endif /* SENSOR_H */
