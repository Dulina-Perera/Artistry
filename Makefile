# Makefile for compiling GTK4 C source files

# Variables
CC = g++
CFLAGS = -std=c++17 -O2
LIBS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi

# Define the target executable.
TARGET = paint-app

# Define source files and corresponding object files.
SRCS = main.cc
OBJS = $(SRCS:.cc=.o)

# Rule to compile source files into object files
%.o: %.ccc
	$(CC) $(CFLAGS) -c -o $@ $<

# Rule to link object files into the executable
$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

# Clean target to remove executable and object files.
clean:
	rm --force $(TARGET) $(OBJS)

# Test target to run the executable.
test: $(TARGET)
	./$(TARGET)

# Phony targets
.PHONY: clean test
