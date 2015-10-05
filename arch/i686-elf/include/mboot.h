/*
 * Copyright (C) 2015 Alek Ratzloff
 *
 * This file is part of Alek's Little Endian Kernel.
 * 
 * Alek's Little Endian Kernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Alek's Little Endian Kernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Alek's Little Endian Kernel.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ALEK_MBOOT_H
#define ALEK_MBOOT_H

#include "terminal.h"

extern "C"
{
  enum mboot_flag
  {
    MBOOT_MEM=1<<0,
    MBOOT_BOOTDEV=1<<1,
    MBOOT_CMDLINE=1<<2,
    MBOOT_MODS=1<<3,
    MBOOT_SYMS=1<<4|1<<5,
    MBOOT_MMAP=1<<6,
    MBOOT_DRIVES=1<<7,
    MBOOT_CONFIG_TABLE=1<<8,
    MBOOT_BOOT_LOADER_NAME=1<<9,
    MBOOT_APM_TABLE=1<<10,
    MBOOT_VBE=1<<11,
  };

  struct mboot_mmap
  {
    u32 size;
    u64 base_addr;
    u64 length;
    u32 type;
  };

  struct MBInfo
  {
    u32 flags;

    u32 mem_lower;
    u32 mem_upper;

    u32 boot_device;

    const char* cmdline;

    u32 mods_count;
    u32 mods_addr;

    u32 syms[8];

    u32 mmap_length;
    mboot_mmap* mmap_addr;

    u32 drives_length;
    u32 drives_addr;

    u32 config_table;

    const char* boot_loader_name;

    u32 apm_table;

    u32 vbe_control_info;
    u32 vbe_mode_info;
    u32 vbe_mode;
    u32 vbe_interface_seg;
    u32 vbe_interface_off;
    u32 vbe_interface_len;
  };

  void debug_flag_info(const MBInfo *mb_info);
}

#endif /* ALEK_MBOOT_H */
