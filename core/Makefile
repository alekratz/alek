CXX_FILES=$(notdir $(shell find . -type f -name \*.cpp))
ASM_FILES=$(notdir $(shell find . -type f -name \*.s))
OBJS=$(CXX_FILES:%.cpp=$(BUILD_DIR)/%.o) \
	$(ASM_FILES:%.s=$(BUILD_DIR)/%.o)

print-%: ; @echo $*=$($*)

ifeq ($(BUILD_DIR),)
	$(error BUILD_DIR not defined)
endif

all: $(OBJS)

$(BUILD_DIR)/%.o: %.s | $(BUILD_DIR)
	$(AS) $(AS_FLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp | $(BUILD_DIR)
	$(CXX) $(CXX_FLAGS) $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)