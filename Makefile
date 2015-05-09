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

TARGET=kernel.img
ELF=kernel.elf
CORE_SRC_FILES:=$(shell find core -type f -name \*.s) \
	$(shell find core -type f -name \*.cpp)
CORE_O_FILES=$(addprefix $(BUILD_DIR)/core/,\
	$(patsubst %.cpp,%.o,$(patsubst %.s,%.o,$(notdir $(CORE_SRC_FILES)))))
ARCH_SRC_FILES:=$(shell find arch/$(ARCH) -type f -name \*.s) \
	$(shell find arch/$(ARCH) -type f -name \*.cpp)
ARCH_O_FILES=$(addprefix $(BUILD_DIR)/arch/,\
	$(patsubst %.cpp,%.o,$(patsubst %.s,%.o,$(notdir $(ARCH_SRC_FILES)))))
O_FILES=$(CORE_O_FILES) $(ARCH_O_FILES)
BUILD_DIR=build
export CXX_FLAGS=-I$(PWD)/include -I$(PWD)/arch/$(ARCH)/include -std=c++14 \
	-ffreestanding -fno-builtin -fno-rtti -fno-exceptions -nostartfiles -O2 -c \
	-Wall
export LD_FLAGS=-nostartfiles -O2
export CXX=$(ARCH)-g++
export AS=$(ARCH)-as
export OBJCOPY=$(ARCH)-objcopy

ifeq ($(ARCH),i686-elf)
	CXX_FLAGS+=
else ifeq ($(ARCH),arm-none-eabi)
	CXX_FLAGS+=-mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s
endif

print-%: ; @echo $*=$($*)

all: $(TARGET)

$(TARGET): check-arch $(ELF)
	$(OBJCOPY) $(ELF) -O binary $(TARGET)

$(ELF): arch core arch/$(ARCH)/link.ld
	@echo linking $(ELF)
	$(CXX) $(LD_FLAGS) $(O_FILES) -T arch/$(ARCH)/link.ld -o $(ELF)

.PHONY: core
core: $(CORE_SRC_FILES)
	@echo building core
	@$(MAKE) -C core BUILD_DIR=../$(BUILD_DIR)/core

.PHONY: arch
arch: $(ARCH_SRC_FILES)
	@echo building $(ARCH)
	@$(MAKE) -C arch BUILD_DIR=../$(BUILD_DIR)/arch

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: check-arch
check-arch:
	@if [ "$(ARCH)" == "" ]; then \
		echo "Unknown architecture '$(ARCH)'. Available targets: i686-elf arm-none-eabi" ; \
		exit 1 ; \
	fi

.PHONY: clean
clean:
	rm -f $(TARGET) $(ELF) 
	rm -rf $(BUILD_DIR)