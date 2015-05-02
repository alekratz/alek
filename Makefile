ARCH=arm-none-eabi
CXX=$(ARCH)-g++
AS=$(ARCH)-as

SRC_DIR=src
BUILD_DIR=build/$(CONFIGURATION)
TARGET=kernel.elf
# Libraries used by this project
LIBS=

override COMPILE_FLAGS+=-Wall -c --std=c++11 -MP -MMD -ffreestanding -nostdlib \
	-fno-builtin -fno-rtti -fno-exceptions -nostartfiles -O2
override LINK_FLAGS+=

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
	@$(MAKE) $(TARGET) --no-print-directory
	
release: export CONFIGURATION=release
# -O2, or whatever optimization preferences you have
release: export COMPILE_FLAGS=-O2 -DNDEBUG
release: dirs
	@mkdir -p $(BUILD_DIR)
	@$(MAKE) $(TARGET) --no-print-directory

# Target symlink
$(TARGET) : $(BUILD_DIR)/$(TARGET)
	@echo "[ LN ] $(BUILD_DIR)/$(TARGET) -> $(TARGET)"
	@rm -f $(TARGET)
	@ln -s $(BUILD_DIR)/$(TARGET) $(TARGET)

# Linking the project together
$(BUILD_DIR)/$(TARGET) : $(O_FILES)
	@echo "[ CXX ] $(notdir $(O_FILES)) -> $(BUILD_DIR)/$(TARGET)"
	@$(CXX) $(LINK_FLAGS) $(O_FILES) -o $(BUILD_DIR)/$(TARGET)

# Directories needed
# TODO : figure out how to remove duplicates from this list
dirs :
	@mkdir -p $(O_DIRS)

# Dependencies
-include $(DEP_FILES)

# Compiling the assembly
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.$(ASM_EXT)
	@echo "[ AS ] $(notdir $<) -> $(notdir $@)"
	@$(AS) $(AS_FLAGS) $< -o $@

# Compiling the C++ sources
$(BUILD_DIR)/%.o : $(SRC_DIR)/%.$(CXX_EXT)
	@echo "[ CXX ] $(notdir $<) -> $(notdir $@)"
	@$(CXX) $(COMPILE_FLAGS) $< -o $@

.PHONY: clean
clean:
	rm -f $(TARGET)
	rm -rf $(BUILD_DIR)
