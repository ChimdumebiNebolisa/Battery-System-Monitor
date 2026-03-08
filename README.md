# Battery System Monitor

A C-based simulation of an embedded battery monitoring system. It simulates battery condition over time, reads values through a sensor layer, runs a firmware-style monitoring loop, enforces safety thresholds, transitions between operating states, and logs major events. Normal and failure scenarios can be run to demonstrate behavior.

## Features

- **Battery simulation:** Voltage, temperature, charge level, and current evolve over time with charging, discharging, and idle behavior.
- **Simulated sensors:** Voltage, temperature, and current are read through a sensor interface separate from the battery model.
- **Monitoring loop:** Each tick: read sensors → safety check → state update → effective mode → battery step → log/print.
- **Safety logic:** Over-voltage (stop charging), over-temperature (shutdown), over-current (warning). Thresholds are in `battery.h`.
- **Operating states:** Idle, charging, discharging, warning, fault. State transitions are driven by sensor readings and safety results; fault overrides normal operation.
- **Event logging:** State transitions, threshold violations, safety shutdowns, and charge/discharge cycle changes are logged with tick and type.
- **Scenarios:** Normal operation (charge/discharge/idle), over-voltage, over-temperature, and over-current scenarios are run to validate responses.

## Project structure

```
Battery-System-Monitor/
├── .gitignore
├── Makefile
├── README.md
├── docs/             # PLAN.md, MILESTONES.md, SPEC.md, GUARDRAILS.md
└── src/
    ├── battery.h/c   # Battery state, thresholds, init/print/step
    ├── sensor.h/c    # Simulated sensor API (voltage, temp, current)
    ├── safety.h/c    # Threshold checks and safety result
    ├── state.h/c     # System state enum and transition rules
    ├── log.h/c       # Event log (state, threshold, shutdown, charge/discharge)
    └── main.c        # Entry point, monitoring loop, scenarios
```

## How to build

You need a C11 compiler and `make`.

**Linux / macOS / WSL:**

```bash
make
```

**Windows (MinGW or MSYS2):**

```bash
make
# or: mingw32-make
```

**Windows (manual with GCC):**

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

The program:

1. Prints initial battery state.
2. Runs **normal scenario:** charge then discharge then idle; no fault/warning when values are within limits.
3. Runs **over-voltage scenario:** voltage above limit; charging is stopped, state goes to warning.
4. Runs **over-temperature scenario:** temperature above limit; system enters fault (shutdown).
5. Runs **over-current scenario:** current above limit; warning is raised.
6. Runs another short normal loop and prints the **event log** (state transitions, threshold violations, shutdowns, charge/discharge cycles).

Output shows tick, state, voltage, temperature, current, and FAULT/WARNING when applicable.

## Documentation

- `docs/PLAN.md` – Build strategy and phases.
- `docs/MILESTONES.md` – Milestone and checkpoint definitions.
- `docs/SPEC.md` – Product goal and features.
- `docs/GUARDRAILS.md` – Workflow and README upkeep.
