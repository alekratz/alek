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

ifeq ($(TARGET),x86)
	export ARCH=i686-elf
	CXX_FLAGS+=-nostdinc -nostdinc++
  AS_FLAGS+=-nostdinc -nostdinc++
	LD_FLAGS+=-nostdlib -nodefaultlibs
else ifeq ($(TARGET),rpi)
	export ARCH=arm-none-eabi
	CXX_FLAGS+=-mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s
endif

IMAGE=kernel.img
ELF=kernel.elf
# Core file information, mostly for dependencies
CORE_SRC_FILES:=$(shell find core -type f -name \*.s) \
	$(shell find core -type f -name \*.cpp)
CORE_O_FILES:=$(patsubst core/%.cpp,build/core/%.o,\
	$(patsubst core/%.s,build/core/%.o,$(CORE_SRC_FILES)))
CORE_DEP_FILES:=$(CORE_O_FILES:%.o=%.d)
# Arch-specific file information, same as above
ARCH_SRC_FILES:=$(shell find arch/$(ARCH) -type f -name \*.s) \
	$(shell find arch/$(ARCH) -type f -name \*.cpp)
ARCH_O_FILES:=$(patsubst arch/$(ARCH)/%.cpp,build/arch/%.o,\
	$(patsubst arch/$(ARCH)/%.s,build/arch/%.o,$(ARCH_SRC_FILES)))
ARCH_DEP_FILES:=$(ARCH_O_FILES:%.o=%.d)
O_FILES=$(CORE_O_FILES) $(ARCH_O_FILES)
BUILD_DIR=build

# Optimization level
O_LEVEL=2

export TOP:=$(PWD)
export CXX_FLAGS+=-I$(TOP)/libc/libc/include -I$(TOP)/libc/libm/include \
	-std=c++14 \
	-ffreestanding -fno-builtin -fno-rtti -fno-exceptions -nostartfiles -O$(O_LEVEL) -c \
	-Wall -MP -MMD
export AS_FLAGS+=
export LD_FLAGS+=-nostartfiles -O2 -L$(BUILD_DIR)/libc -lc -lm -lgcc
export CXX=$(ARCH)-g++
export AS=$(ARCH)-as
export OBJCOPY=$(ARCH)-objcopy

print-%: ; @echo $*=$($*)

all: $(IMAGE)

$(IMAGE): check-arch $(ELF)
	@echo == copying image
	@echo [ OBJCOPY ] $(IMAGE)
	@$(OBJCOPY) $(ELF) -O binary $(IMAGE)

$(ELF): arch core libs arch/$(ARCH)/link.ld
	@echo == linking $(ELF)
	@echo [ LD ] $(ELF)
	@$(CXX) $(O_FILES) -T arch/$(ARCH)/link.ld -o $(ELF) $(LD_FLAGS)

.PHONY: libs
libs:
	@echo == building libs
	@$(MAKE) -C libc BUILD_DIR=../$(BUILD_DIR)/libc

.PHONY: core
core: libs $(CORE_SRC_FILES)
	@echo == building core
	@$(MAKE) -C core BUILD_DIR=../$(BUILD_DIR)/core DEP_FILES="$(CORE_DEP_FILES)" \
		CXX_FLAGS="$(CXX_FLAGS) -I$(TOP)/core/include -I$(TOP)/arch/$(ARCH)/include" \
    AS_FLAGS="$(AS_FLAGS) -I$(TOP)/core/include -I$(TOP)/arch/$(ARCH)/include"

.PHONY: arch
arch: libs $(ARCH_SRC_FILES)
	@echo == building $(ARCH)
	@$(MAKE) -C arch BUILD_DIR=../$(BUILD_DIR)/arch DEP_FILES="$(ARCH_DEP_FILES)" \
		CXX_FLAGS="$(CXX_FLAGS) -I$(TOP)/core/include -I$(TOP)/arch/$(ARCH)/include" \
    AS_FLAGS="$(AS_FLAGS) -I$(TOP)/core/include -I$(TOP)/arch/$(ARCH)/include"

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: check-arch
check-arch:
	@if [ "$(ARCH)" == "" ]; then \
		echo "Unknown target '$(TARGET)'. Available targets: x86 rpi" ; \
		exit 1 ; \
	fi

.PHONY: test
test:
	@echo == building tests
	@$(MAKE) -C test BUILD_DIR=../$(BUILD_DIR)/test

.PHONY: clean
clean:
	rm -f $(IMAGE) $(ELF) 
	rm -rf $(BUILD_DIR)
