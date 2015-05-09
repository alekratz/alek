CXX_FILES=$(notdir $(shell find . -type f -name \*.cpp))
ASM_FILES=$(notdir $(shell find . -type f -name \*.s))
OBJS=$(CXX_FILES:%.cpp=$(BUILD_DIR)/%.o) \
	$(ASM_FILES:%.s=$(BUILD_DIR)/%.o)

ifeq ($(BUILD_DIR),)
	$(error BUILD_DIR not defined)
endif

all: $(OBJS)

$(BUILD_DIR)/%.o: %.s
	$(AS) $(AS_FLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $< -o $@