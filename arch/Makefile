#
# Copyright (C) 2015 Alek Ratzloff
# 
# This file is part of Alek's Little Endian Kernel.
# 
# Alek's Little Endian Kernel is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# Alek's Little Endian Kernel is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with Alek's Little Endian Kernel.  If not, see <http://www.gnu.org/licenses/>.
# 

CXX_FILES=$(shell find $(ARCH) -type f -name \*.cpp)
ASM_FILES=$(shell find $(ARCH) -type f -name \*.S)
OBJS=$(CXX_FILES:$(ARCH)/%=$(BUILD_DIR)/%.o) \
	$(ASM_FILES:$(ARCH)/%=$(BUILD_DIR)/%.o)
OBJ_DIRS=$(sort $(dir $(OBJS)))

print-%: ; @echo "$*=$($*)"

ifeq ($(BUILD_DIR),)
	$(error BUILD_DIR not defined)
endif

all: $(OBJS)

-include $(DEP_FILES)
$(BUILD_DIR)/%.cpp.o: $(ARCH)/%.cpp | $(OBJ_DIRS)
	@echo [ CXX ] $<
	@$(CXX) $(CXX_FLAGS) $< -o $@

$(BUILD_DIR)/%.S.o: $(ARCH)/%.S | $(OBJ_DIRS)
	@echo [ AS ] $<
#@$(CPP) $(AS_FLAGS) $< | $(AS) $(AS_FLAGS) -o $@
	@$(AS) $(AS_FLAGS) $< -o $@

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)
