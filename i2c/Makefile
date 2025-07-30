# Compiler and flags
CC := arm-poky-linux-musleabi-gcc
SYSROOT := /opt/poky-tiny/2.5.2/sysroots/cortexa5hf-neon-poky-linux-musleabi
CFLAGS := -march=armv7-a -marm -mfpu=neon -mfloat-abi=hard -mcpu=cortex-a5 -mmusl --sysroot=$(SYSROOT) -Iinclude

# Directories
SRC_DIR := src
BUILD_DIR := build

# Output
LIB := $(BUILD_DIR)/libi2c.a

# Files
SRC := $(SRC_DIR)/rb_i2c.c
OBJ := $(BUILD_DIR)/i2c.o

# Default target
all: $(LIB)

# Build static library
$(LIB): $(OBJ)
	@mkdir -p $(BUILD_DIR)
	arm-poky-linux-musleabi-ar rcs $@ $^

# Compile object file
$(OBJ): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf $(BUILD_DIR)
