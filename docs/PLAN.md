# PLAN.md

## Objective
Build Battery System Monitor as a focused C project that simulates an embedded battery monitoring system with sensor-driven monitoring, safety checks, state transitions, and event logging.

## Project outcome
The finished project should:
- simulate changing battery conditions over time
- expose simulated sensor readings for voltage, temperature, and current
- run a firmware-style monitoring loop
- detect unsafe conditions using threshold-based safety logic
- transition between operating states such as idle, charging, discharging, warning, and fault/shutdown
- log meaningful events during normal and abnormal operation
- produce understandable runtime output that shows what the system is doing

## Build strategy
The project should be built from the inside out.

Start with the smallest working battery simulation.
Then add the monitoring loop.
Then layer in safety logic.
Then add explicit operating states.
Then add logging and scenario coverage.
Do not start with polish, visualization, or extra infrastructure.

## Development phases

### Phase 1: Establish the simulation base
Create the project skeleton in C and define the core battery data model.

This phase should answer:
- what values define battery condition
- how those values are stored
- how battery values change across time steps

Target result:
A simple executable can run a repeated simulation step and show battery values changing over time.

### Phase 2: Add the monitoring structure
Introduce the firmware-style control loop and sensor abstraction.

This phase should answer:
- how the monitor reads battery-related values
- how each simulation step is processed
- how the loop is structured so it feels like embedded logic rather than random program flow

Target result:
The program repeatedly reads simulated sensor values and processes them in a clear loop.

### Phase 3: Add safety enforcement
Implement threshold-based checks and protective responses.

This phase should answer:
- what counts as unsafe voltage, temperature, and current
- what the system does when those limits are crossed
- how safety logic overrides normal behavior

Target result:
The system can detect unsafe battery conditions and respond in a clear, deterministic way.

### Phase 4: Make behavior state-driven
Define explicit operating states and transition rules.

This phase should answer:
- what operational states the monitor can be in
- what causes transitions between them
- how warning and fault behavior differ from normal operation

Target result:
The project behaves like a state-based embedded system instead of a loose collection of checks.

### Phase 5: Improve observability
Add event logging and better runtime output.

This phase should answer:
- what important events should be visible
- how a user can inspect behavior over time
- how to make abnormal behavior obvious without creating noisy output

Target result:
Someone running the program can understand what happened, when it happened, and why.

### Phase 6: Validate scenarios and clean up
Run both normal and failure scenarios, then tighten the project.

This phase should answer:
- does normal operation look believable
- do failure conditions trigger the intended responses
- is the code clean, focused, and easy to explain

Target result:
The project is presentation-ready and clearly demonstrates embedded systems thinking in C.

## Priorities
Prioritize work in this order:
1. correctness of the battery simulation flow
2. clarity of the monitoring loop
3. correctness of safety handling
4. consistency of state transitions
5. usefulness of logs and output
6. cleanup and presentation quality

## Decision rules
Use these rules while building:

### Rule 1: Protect the project’s identity
Every addition should make the project feel more like an embedded battery monitoring simulation.

### Rule 2: Prefer clarity over cleverness
Use straightforward logic and readable structure.
Do not over-engineer abstractions.

### Rule 3: Make safety logic obvious
Safety checks and protective behavior should be easy to find and understand.

### Rule 4: Keep state explicit
Do not let system state become implicit or scattered.

### Rule 5: Build only what the core concept needs
Do not add cloud features, web backends, fancy dashboards, databases, or unrelated extras to the core version.

## Risks to avoid
These are the main ways the project can go wrong:

- turning it into a generic console app with weak embedded systems identity
- adding too much complexity before the core loop works
- burying safety logic inside messy control flow
- creating vague or inconsistent state transitions
- focusing on output formatting before behavior is correct
- drifting into real hardware or industrial-system claims the project does not support

## What to keep checking during development
As the project evolves, keep checking:
- does the monitoring loop remain the center of the system
- are voltage, temperature, current, and charge behavior still easy to follow
- do safety rules clearly affect system behavior
- do state transitions make sense
- are the logs meaningful
- does the project still feel focused and portfolio-worthy

## Completion standard
The project is in good shape when:
- the battery simulation is working
- the monitoring loop is stable and readable
- unsafe conditions trigger the right responses
- state transitions are explicit and coherent
- logs explain major events
- both normal and abnormal scenarios can be demonstrated clearly
- the final result feels like a disciplined C-based embedded systems simulation