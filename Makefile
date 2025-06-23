# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Isingle_include

# Output and sources
TARGET = task-cli
SRC = main.cpp

# Default target
all: $(TARGET)

# Build target
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

# Clean up build artifacts
clean:
	rm -f $(TARGET) a.out

.PHONY: all run clean