# Makefile for Battery System Monitor
# Builds the Milestone 1 core simulation.

CC     = gcc
CFLAGS = -Wall -Wextra -std=c11
SRC    = src/main.c src/battery.c
OBJ    = src/main.o src/battery.o
TARGET = battery_monitor

.PHONY: all clean run

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

src/main.o: src/main.c src/battery.h
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/battery.o: src/battery.c src/battery.h
	$(CC) $(CFLAGS) -c src/battery.c -o src/battery.o

clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	./$(TARGET)
