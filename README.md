# Battery System Monitor

A C-based simulation of an embedded battery monitoring system. It models battery condition over time (voltage, temperature, charge level, current), with a structure that will support sensor-style reading, safety rules, and state-based behavior.

## Current state (Milestone 1)

- **Project skeleton:** Source and headers in `src/`, build via Makefile.
- **Battery data model:** `BatteryState` (voltage, temperature, charge level, current), threshold constants, default initial state, and helpers to print state.
- **Basic simulation:** `battery_step()` updates state over time with idle, charging, and discharging behavior; values change in plausible directions.

## Project structure

```
Battery-System-Monitor/
├── Makefile          # Build: make all, make run, make clean
├── README.md
├── docs/             # Plan, milestones, spec, guardrails
└── src/
    ├── battery.h     # Battery state, thresholds, init/print/step API
    ├── battery.c     # Battery model and simulation logic
    └── main.c        # Entry point, runs a short simulation demo
```

## How to build

You need a C11 compiler and (for the Makefile) `make`.

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
gcc -Wall -Wextra -std=c11 -c src/main.c -o src/main.o
gcc -o battery_monitor src/main.o src/battery.o
```

## How to run

After building:

```bash
./battery_monitor
```

On Windows (e.g. MinGW): `battery_monitor.exe` or `.\battery_monitor.exe`.

The program prints the initial battery state, then runs a short sequence of charging, discharging, and idle steps and prints the state after each step.

## Documentation

- `docs/PLAN.md` – Build strategy and phases.
- `docs/MILESTONES.md` – Milestone and checkpoint definitions.
- `docs/SPEC.md` – Product goal and features.
- `docs/GUARDRAILS.md` – Workflow and README upkeep.
