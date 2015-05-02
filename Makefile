ARCH=arm-none-eabi
CXX=$(ARCH)-g++
AS=$(ARCH)-as
OBJCOPY=$(ARCH)-objcopy

SRC_DIR=src
BUILD_DIR=build/$(CONFIGURATION)
IMAGE=boot/kernel.img
TARGET=kernel.elf
# Libraries used by this project
LIBS=

override COMPILE_FLAGS+=-Wall -c --std=c++11 -MP -MMD -ffreestanding -nostdlib \
	-fno-builtin -fno-rtti -fno-exceptions -nostartfiles -O2 -mfpu=vfp -mfloat-abi=hard \
	-march=armv6zk -mtune=arm1176jzf-s
override LINK_FLAGS+=-nostdlib -nostartfiles -Ofast

print-%: ; @echo $*=$($*)

# cpp, cxx, c, C, etc
CXX_EXT=cpp
ASM_EXT=s

# Files and directories
CXX_SRC_FILES=$(shell find $(SRC_DIR) -name *.$(CXX_EXT) -type f) 
ASM_SRC_FILES=$(shell find $(SRC_DIR) -name *.$(ASM_EXT) -type f)
CXX_O_FILES=$(CXX_SRC_FILES:$(SRC_DIR)/%.$(CXX_EXT)=$(BUILD_DIR)/%.o)
ASM_O_FILES=$(ASM_SRC_FILES:$(SRC_DIR)/%.$(ASM_EXT)=$(BUILD_DIR)/%.o)
O_FILES=$(ASM_O_FILES) $(CXX_O_FILES)
O_DIRS=$(dir $(O_FILES))
DEP_FILES=$(O_FILES:.o=.d)

# To change the default 'make' action, set this to debug or release
all : debug

.PHONY: debug release
debug: export CONFIGURATION=debug
debug: export COMPILE_FLAGS=-g -DDEBUG
debug: dirs
	@mkdir -p $(BUILD_DIR)
	@echo "Starting debug build"
	@$(MAKE) $(IMAGE) --no-print-directory
	
release: export CONFIGURATION=release
# -O2, or whatever optimization preferences you have
release: export COMPILE_FLAGS=-DNDEBUG
release: dirs
	@mkdir -p $(BUILD_DIR)
	@echo "Starting release build"
	@$(MAKE) $(IMAGE) --no-print-directory

$(IMAGE): $(TARGET)
	@echo "[ OBJCOPY ] $(TARGET) -> $(IMAGE)"
	@$(OBJCOPY) $(TARGET) -O binary $(IMAGE)

# Target symlink
$(TARGET): $(BUILD_DIR)/$(TARGET)
	@echo "[ LN ] $(BUILD_DIR)/$(TARGET) -> $(TARGET)"
	@rm -f $(TARGET)
	@ln -s $(BUILD_DIR)/$(TARGET) $(TARGET)

# Linking the project together
$(BUILD_DIR)/$(TARGET): $(O_FILES) $(SRC_DIR)/linker.ld
	@echo "[ LD ] $(notdir $(O_FILES)) -> $(BUILD_DIR)/$(TARGET)"
	@$(CXX) $(LINK_FLAGS) $(O_FILES) -T $(SRC_DIR)/linker.ld -o $(BUILD_DIR)/$(TARGET)

# Directories needed
# TODO : figure out how to remove duplicates from this list
dirs:
	@mkdir -p $(O_DIRS) boot

# Dependencies
-include $(DEP_FILES)

# Compiling the assembly
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(ASM_EXT)
	@echo "[ AS ] $(notdir $<) -> $(notdir $@)"
	@$(AS) $(AS_FLAGS) $< -o $@

# Compiling the C++ sources
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.$(CXX_EXT)
	@echo "[ CXX ] $(notdir $<) -> $(notdir $@)"
	@$(CXX) $(COMPILE_FLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET) $(IMAGE)
	rm -rf $(BUILD_DIR)
