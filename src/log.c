/**
 * log.c - Simple in-memory event log.
 */

#include "log.h"
#include <stdio.h>
#include <string.h>

static LogEntry s_log[LOG_ENTRIES_MAX];
static int s_count;

void log_clear(void) {
	s_count = 0;
}

void log_event(int tick, LogEventType type, const char *msg) {
	if (s_count >= LOG_ENTRIES_MAX) return;
	LogEntry *e = &s_log[s_count++];
	e->tick = tick;
	e->type = type;
	if (msg) {
		size_t n = sizeof(e->msg) - 1;
		strncpy(e->msg, msg, n);
		e->msg[n] = '\0';
	} else {
		e->msg[0] = '\0';
	}
}

static const char *log_type_str(LogEventType t) {
	switch (t) {
	case LOG_STATE_TRANSITION:   return "state";
	case LOG_THRESHOLD_VIOLATION: return "threshold";
	case LOG_SAFETY_SHUTDOWN:    return "shutdown";
	case LOG_CHARGE_CYCLE:       return "charge";
	case LOG_DISCHARGE_CYCLE:    return "discharge";
	default:                     return "?";
	}
}

void log_print_all(void) {
	for (int i = 0; i < s_count; i++) {
		const LogEntry *e = &s_log[i];
		printf("  [tick %3d] %-10s %s\n", e->tick, log_type_str(e->type), e->msg);
	}
}
