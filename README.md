# Battery System Monitor

C simulation of an embedded battery monitor: sensor loop, safety thresholds, state machine (idle/charging/discharging/warning/fault), and event logging. Includes normal and failure scenarios.

## Features

- Battery simulation (voltage, temperature, SOC, current) with charge/discharge/idle
- Sensor interface (voltage, temp, current) separate from battery model
- Monitoring loop: read sensors → safety check → state update → battery step → log
- Safety: over-voltage (stop charge), over-temp (shutdown), over-current (warning); thresholds in `battery.h`
- States: idle, charging, discharging, warning, fault; fault overrides normal operation
- Event log: state transitions, threshold violations, shutdowns, charge/discharge cycles
- Scenarios: normal, over-voltage, over-temp, over-current

## Project structure

```
Battery-System-Monitor/
├── .gitignore
├── Makefile
├── README.md
└── src/
    ├── battery.h/c   # Battery state, thresholds, init/print/step
    ├── sensor.h/c    # Simulated sensor API (voltage, temp, current)
    ├── safety.h/c    # Threshold checks and safety result
    ├── state.h/c     # System state enum and transition rules
    ├── log.h/c       # Event log (state, threshold, shutdown, charge/discharge)
    └── main.c        # Entry point, monitoring loop, scenarios
```

## How to build

Requires a C11 compiler and `make`. From the project root:

```bash
make
```

(On Windows with MinGW/MSYS2 use the same; or `mingw32-make` if that’s what you have.)

**Without make (manual):**

```bash
gcc -Wall -Wextra -std=c11 -c src/battery.c -o src/battery.o
gcc -Wall -Wextra -std=c11 -c src/sensor.c -o src/sensor.o
gcc -Wall -Wextra -std=c11 -c src/safety.c -o src/safety.o
gcc -Wall -Wextra -std=c11 -c src/state.c -o src/state.o
gcc -Wall -Wextra -std=c11 -c src/log.c -o src/log.o
gcc -Wall -Wextra -std=c11 -c src/main.c -o src/main.o
gcc -o battery_monitor src/main.o src/battery.o src/sensor.o src/safety.o src/state.o src/log.o
```

## How to run

```bash
./battery_monitor
```

On Windows: `battery_monitor.exe` or `.\battery_monitor.exe`.

Runs initial state, then the four scenarios (normal, over-voltage, over-temp, over-current), then a short loop whose event log is printed. Each step shows tick, state, V, T, I, and FAULT/WARNING when applicable.
