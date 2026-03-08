# MILESTONES.md

## Milestone 1: Core simulation foundation

### Goal
Set up the project structure and build the basic battery simulation data flow in C.

### Checkpoint 1.1: Project skeleton is ready
- Create the project folder structure.
- Add initial source and header files.
- Add a simple build command or Makefile.
- Confirm the project compiles and runs a minimal entry point.

**Done means:** the project builds successfully and runs a basic executable.

### Checkpoint 1.2: Battery data model exists
- Define a battery data structure for voltage, temperature, charge level, and current.
- Define constants or configuration values for safe operating thresholds.
- Create an initial battery state with default starting values.
- Add helper functions to print or inspect battery values.

**Done means:** battery state can be created, stored, and displayed cleanly.

### Checkpoint 1.3: Basic battery simulation works
- Create a function that updates battery values over time.
- Add simple charging behavior.
- Add simple discharging behavior.
- Make battery values change in believable directions across simulation steps.

**Done means:** the battery values evolve across repeated simulation steps.

---

## Milestone 2: Sensor and monitoring loop

### Goal
Create the firmware-style monitoring cycle that reads simulated sensor values and processes the battery state.

### Checkpoint 2.1: Simulated sensor layer is added
- Create functions that return simulated voltage readings.
- Create functions that return simulated temperature readings.
- Create functions that return simulated current readings.
- Keep the sensor interface separate from the battery model.

**Done means:** the monitoring system can read battery-related values through a sensor-like interface.

### Checkpoint 2.2: Monitoring loop is implemented
- Create the main control loop for the simulation.
- Read sensor values during each loop iteration.
- Store or pass the current readings into the monitoring logic.
- Print or record each loop step for inspection.

**Done means:** the program repeatedly reads simulated sensor values in a structured control loop.

### Checkpoint 2.3: Time-step flow is stable
- Add a loop counter or simulation tick value.
- Ensure each cycle updates battery behavior before the next reading.
- Verify the simulation runs for multiple steps without breaking.
- Keep the execution order clear and consistent.

**Done means:** the simulation behaves like a repeatable firmware-style monitoring cycle.

---

## Milestone 3: Safety rules and thresholds

### Goal
Add safety monitoring logic that detects unsafe battery conditions and triggers protective responses.

### Checkpoint 3.1: Threshold checks exist
- Add over-voltage detection.
- Add over-temperature detection.
- Add unsafe current detection.
- Make threshold values easy to identify and update.

**Done means:** unsafe conditions can be detected from current sensor readings.

### Checkpoint 3.2: Protective responses are defined
- Create logic to stop charging on over-voltage.
- Create logic to trigger shutdown on dangerous temperature.
- Create logic to raise warnings on unsafe current draw.
- Ensure each safety condition produces a clear system response.

**Done means:** the program reacts to unsafe conditions instead of only detecting them.

### Checkpoint 3.3: Safety handling is validated
- Simulate a case that exceeds voltage limits.
- Simulate a case that exceeds temperature limits.
- Simulate a case that exceeds current limits.
- Verify the expected responses happen in each case.

**Done means:** each major safety rule has been exercised and behaves correctly.

---

## Milestone 4: Operating states and transitions

### Goal
Implement state-based system behavior so the battery monitor behaves like embedded control software.

### Checkpoint 4.1: System states are defined
- Create an enum or equivalent for idle, charging, discharging, warning, and fault/shutdown.
- Add a field that stores the current system state.
- Add a readable way to display the active state.

**Done means:** the program has explicit operating states.

### Checkpoint 4.2: State transition rules are implemented
- Add logic for entering charging state.
- Add logic for entering discharging state.
- Add logic for moving into warning state when conditions become risky.
- Add logic for moving into fault or shutdown state when conditions become unsafe.

**Done means:** system state changes are driven by battery conditions and safety results.

### Checkpoint 4.3: State behavior is coherent
- Prevent contradictory states from appearing at the same time.
- Ensure fault or shutdown state overrides normal operation when needed.
- Verify warning state does not behave like a hard failure unless escalation happens.
- Confirm normal states resume only when allowed by the logic.

**Done means:** the state machine behaves consistently and predictably.

---

## Milestone 5: Event logging and observability

### Goal
Add logging so the simulation clearly shows what happened and why.

### Checkpoint 5.1: Event logging system exists
- Create a simple event log structure or logging mechanism.
- Log important events instead of every tiny detail.
- Include the simulation tick or step number in each event.
- Make logs easy to read in program output.

**Done means:** meaningful events can be recorded and reviewed.

### Checkpoint 5.2: Major events are logged
- Log state transitions.
- Log threshold violations.
- Log safety shutdowns.
- Log charge and discharge cycle changes.

**Done means:** the most important system actions and incidents are visible in logs.

### Checkpoint 5.3: Runtime output is understandable
- Print battery values during the simulation.
- Print the active operating state during each step.
- Show warnings and faults clearly.
- Keep output readable and not overly noisy.

**Done means:** someone running the program can understand the system’s behavior over time.

---

## Milestone 6: Scenario coverage and final polish

### Goal
Exercise the system across realistic scenarios and clean up the project into a solid finished version.

### Checkpoint 6.1: Normal-operation scenarios work
- Run a normal charging scenario.
- Run a normal discharging scenario.
- Verify values change in expected directions.
- Verify the system stays out of warning and fault states when conditions are safe.

**Done means:** normal behavior works and looks believable.

### Checkpoint 6.2: Failure scenarios work
- Run an overheating scenario.
- Run an over-voltage scenario.
- Run an unsafe current scenario.
- Verify warnings, faults, and protective responses happen as expected.

**Done means:** abnormal behavior is handled correctly and visibly.

### Checkpoint 6.3: Project is cleaned up
- Remove dead code and redundant logic.
- Improve naming where needed.
- Make module boundaries clearer if needed.
- Add or refine README run instructions.

**Done means:** the project is clean, understandable, and ready to present.

---

## Final completion standard
Battery System Monitor is complete when:
- battery values are simulated over time
- sensor readings are processed through a firmware-style loop
- safety thresholds detect unsafe conditions
- protective responses trigger correctly
- operating states transition clearly
- important events are logged
- both normal and failure scenarios can be demonstrated
- the project feels like a focused embedded systems simulation in C