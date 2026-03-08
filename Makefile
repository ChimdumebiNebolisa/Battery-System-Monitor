# Makefile for Battery System Monitor
# Builds full simulation: battery, sensors, safety, state, logging, scenarios.

CC     = gcc
CFLAGS = -Wall -Wextra -std=c11
OBJ    = src/main.o src/battery.o src/sensor.o src/safety.o src/state.o src/log.o
TARGET = battery_monitor

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

src/main.o: src/main.c src/battery.h src/sensor.h src/safety.h src/state.h src/log.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/battery.o: src/battery.c src/battery.h
	$(CC) $(CFLAGS) -c src/battery.c -o src/battery.o

src/sensor.o: src/sensor.c src/sensor.h
	$(CC) $(CFLAGS) -c src/sensor.c -o src/sensor.o

src/safety.o: src/safety.c src/safety.h src/battery.h
	$(CC) $(CFLAGS) -c src/safety.c -o src/safety.o

src/state.o: src/state.c src/state.h src/safety.h src/battery.h
	$(CC) $(CFLAGS) -c src/state.c -o src/state.o

src/log.o: src/log.c src/log.h
	$(CC) $(CFLAGS) -c src/log.c -o src/log.o

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
