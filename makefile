# Compilers and flags
CC  = gcc      # C compiler
CXX = g++      # C++ compiler
CFLAGS = -g
CXXFLAGS = -g

# Directories
SRC_DIR = src
PRCS_SRC_DIR = src/processes
OBJ_DIR = obj

# Target
TARGET = main

# =====================================
# Source file detection
# =====================================

# C source files (excluding specific ones)
SRC_C = $(filter-out \
	$(SRC_DIR)/test.c \
	$(SRC_DIR)/endian_reverser.c \
	$(SRC_DIR)/menu.c, \
	$(wildcard $(SRC_DIR)/*.c))

# C++ source files
SRC_CPP = $(wildcard $(SRC_DIR)/*.cpp)
PRCS_CPP = $(wildcard $(PRCS_SRC_DIR)/*.cpp)

# =====================================
# Object file generation
# =====================================

OBJ_C     = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_C))
OBJ_CPP   = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRC_CPP))
PRCS_OBJ  = $(patsubst $(PRCS_SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(PRCS_CPP))

OBJ = $(OBJ_C) $(OBJ_CPP) $(PRCS_OBJ)

# =====================================
# Build rules
# =====================================

all: $(TARGET)

# Link using C++ compiler
$(TARGET): $(OBJ)
	$(CXX) -o $@ $(OBJ)

# Compile C files with gcc
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ files in src/ with g++
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile C++ files in src/processes/ with g++
$(OBJ_DIR)/%.o: $(PRCS_SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure obj directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR) $(TARGET)

.PHONY: all clean
