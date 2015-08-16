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

C_FILES=$(shell find . -type f -name \*.c)
CXX_FILES=$(shell find . -type f -name \*.cpp)
ASM_FILES=$(shell find . -type f -name \*.s)
OBJS=$(C_FILES:%.c=$(BUILD_DIR)/%.o) \
	$(CXX_FILES:%.cpp=$(BUILD_DIR)/%.o) \
	$(ASM_FILES:%.s=$(BUILD_DIR)/%.o)
OBJ_DIRS=$(sort $(dir $(OBJS)))

print-%: ; @echo $*=$($*)

ifeq ($(BUILD_DIR),)
	$(error BUILD_DIR not defined)
endif

-include $(DEP_FILES)

all: $(OBJS)

$(BUILD_DIR)/%.o: %.s | $(OBJ_DIRS)
	@echo [ AS ] $<
	@$(AS) $(AS_FLAGS) $< -o $@

$(BUILD_DIR)/%.o: %.cpp | $(OBJ_DIRS)
	@echo [ CXX ] $<
	@$(CXX) $(CXX_FLAGS) $< -o $@

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)