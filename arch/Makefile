CXX_FILES=$(notdir $(shell find $(ARCH) -type f -name \*.cpp))
ASM_FILES=$(notdir $(shell find $(ARCH) -type f -name \*.s))
OBJS=$(CXX_FILES:%.cpp=$(BUILD_DIR)/%.o) \
	$(ASM_FILES:%.s=$(BUILD_DIR)/%.o)

print-%: ; @echo $*=$($*)

ifeq ($(BUILD_DIR),)
	$(error BUILD_DIR not defined)
endif

all: $(OBJS)

$(BUILD_DIR)/%.o: $(ARCH)/%.cpp
	$(CXX) $(CXX_FLAGS) $< -o $@

$(BUILD_DIR)/%.o: $(ARCH)/%.s
	$(AS) $(AS_FLAGS) $< -o $@