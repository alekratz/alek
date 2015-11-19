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

# Generic libc library
LIBC_SRC_FILES:=$(shell find libc -type f -name \*.S) \
	$(shell find libc -type f -name \*.cpp)
LIBC_O_FILES:=$(patsubst libc/%,$(BUILD_DIR)/libc/%.o,$(LIBC_SRC_FILES))
LIBC_DEP_FILES:=$(LIBC_O_FILES:%.o=%.d)
# Mathematics library
LIBM_SRC_FILES:=$(shell find libm -type f -name \*.S) \
	$(shell find libm -type f -name \*.cpp)
LIBM_O_FILES:=$(patsubst libm/%,$(BUILD_DIR)/libm/%.o,$(LIBM_SRC_FILES))
LIBM_DEP_FILES:=$(LIBM_O_FILES:%.o=%.d)

print-%: ; @echo $*=$($*)

ifeq ($(BUILD_DIR),)
	$(error BUILD_DIR not defined)
endif

LIBC_TARGET=$(BUILD_DIR)/libc.a
LIBM_TARGET=$(BUILD_DIR)/libm.a

all: $(LIBC_TARGET) $(LIBM_TARGET)

$(LIBC_TARGET): libc $(LIBC_O_FILES)
	@echo == linking $(LIBC_TARGET)
	@echo [ AR ] $(LIBC_TARGET)
	@$(AR) rcs $(LIBC_TARGET) $(LIBC_O_FILES)

$(LIBM_TARGET): libm $(LIBM_O_FILES)
	@echo == linking $(LIBM_TARGET)
	@echo [ AR ] $(LIBM_TARGET)
	@$(AR) rcs $(LIBM_TARGET) $(LIBM_O_FILES)

.PHONY: libc
libc: $(LIBC_SRC_FILES)
	@echo == building libc
	@$(MAKE) -C libc BUILD_DIR="../$(BUILD_DIR)/libc" DEP_FILES="$(LIBC_DEP_FILES)"

.PHONY: libm
libm: $(LIBM_SRC_FILES)
	@echo == building libm
	@$(MAKE) -C libm BUILD_DIR="../$(BUILD_DIR)/libm" DEP_FILES="$(LIBM_DEP_FILES)"