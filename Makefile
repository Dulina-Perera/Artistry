# Makefile - The makefile for the Artistry application

# Variables
CC = g++
CFLAGS = -std=c++17 -O2 -Iinclude -I/usr/include
LIBS = -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi -lGL -lGLU -limgui -lglad

# Target executable
TARGET = artistry

INCLUDE_DIR = include
SRC_DIR = src
BUILD_DIR = build

# Source files and object files
SRCS = $(wildcard $(SRC_DIR)/*.cc $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.cc,$(BUILD_DIR)/%.o,$(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS)))

# Ensure the build directory exists.
$(BUILD_DIR):
	mkdir --parents $(BUILD_DIR)

# Rule to compile C++ source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to compile C source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files into the target executable
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

# Phony targets
.PHONY: clean debug run

# Target to clean the build artifacts
clean:
	rm --force $(BUILD_DIR)/*.o $(TARGET)

# Target to run the executable in debug mode using gdb
debug: $(TARGET)
	gdb ./$(TARGET)

# Target to run the executable
run: $(TARGET)
	./$(TARGET)
