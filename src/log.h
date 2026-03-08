/**
 * log.h - Event logging for the monitoring system.
 * Important events only; each entry includes tick and is readable in output.
 */

#ifndef LOG_H
#define LOG_H

#define LOG_MSG_MAX 80
#define LOG_ENTRIES_MAX 128

typedef enum {
	LOG_STATE_TRANSITION,
	LOG_THRESHOLD_VIOLATION,
	LOG_SAFETY_SHUTDOWN,
	LOG_CHARGE_CYCLE,
	LOG_DISCHARGE_CYCLE
} LogEventType;

typedef struct {
	int tick;
	LogEventType type;
	char msg[LOG_MSG_MAX];
} LogEntry;

/**
 * Clear the log (e.g. at start of a scenario).
 */
void log_clear(void);

/**
 * Record an event with current simulation tick.
 */
void log_event(int tick, LogEventType type, const char *msg);

/**
 * Print all logged events to stdout in readable form.
 */
void log_print_all(void);

#endif /* LOG_H */
