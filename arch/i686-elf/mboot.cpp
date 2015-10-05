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

#include "mboot.h"
#include "terminal.h"

#define HAS_FLAG(n,f) ((n) & (f))

void debug_flag_info(const MBInfo *mb_info)
{
  //Terminal& TERMINST() = Terminal::get_instance();
  TERMINST().printf("flags: %\n", mb_info->flags);

  if(HAS_FLAG(mb_info->flags, MBOOT_MEM))
  {
    TERMINST().printf("mem_lower: %kb\n", mb_info->mem_lower);
    TERMINST().printf("mem_upper: %kb\n", mb_info->mem_upper);
  }
  else
  {
    TERMINST().puts("-- mem fields unavailable\n");
  }
  if(HAS_FLAG(mb_info->flags, MBOOT_BOOTDEV))
    TERMINST().printf("boot_device: %\n", mb_info->boot_device);
  else
  {
    TERMINST().puts("-- boot_device field unavailable\n");
  }
  if(HAS_FLAG(mb_info->flags, MBOOT_CMDLINE))
    TERMINST().printf("cmdline: %\n", mb_info->cmdline);
  else
  {
    TERMINST().puts("-- cmdline field unavailable\n");
  }
  if(HAS_FLAG(mb_info->flags, MBOOT_MODS))
  {
    TERMINST().printf("mods_count: %\n", mb_info->mods_count);
    TERMINST().printf("mods_addr: %\n", mb_info->mods_addr);
  }
  else
  {
    TERMINST().puts("-- mods fields unavailable\n");
  }
  //TERMINST().printf("syms: %\n", syms[mb_info->8]);
  if(HAS_FLAG(mb_info->flags, MBOOT_MMAP))
  {
    TERMINST().printf("mmap_addr: %\n", mb_info->mmap_addr);
    TERMINST().printf("mmap_length: %\n", mb_info->mmap_length);
  }
  else
  {
    TERMINST().puts("-- mmap fields unavailable\n");
  }

  if(HAS_FLAG(mb_info->flags, MBOOT_DRIVES))
  {
    TERMINST().printf("drives_length: %\n", mb_info->drives_length);
    TERMINST().printf("drives_addr: %\n", mb_info->drives_addr);
  }
  else
    TERMINST().puts("-- drives fields unavailable\n");

  if(HAS_FLAG(mb_info->flags, MBOOT_CONFIG_TABLE))
    TERMINST().printf("config_table: %\n", mb_info->config_table);
  else
    TERMINST().puts("-- config table field unavailable\n");

  if(HAS_FLAG(mb_info->flags, MBOOT_BOOT_LOADER_NAME))
    TERMINST().printf("boot_loader_name: %\n", mb_info->boot_loader_name);
  else
    TERMINST().puts("-- boot loader name field unavailable\n");

  if(HAS_FLAG(mb_info->flags, MBOOT_APM_TABLE))
    TERMINST().printf("apm_table: %\n", mb_info->apm_table);
  else
    TERMINST().puts("-- apm table field unavailable\n");

  if(HAS_FLAG(mb_info->flags, MBOOT_VBE))
  {
    TERMINST().printf("vbe_control_info: %\n", mb_info->vbe_control_info);
    TERMINST().printf("vbe_mode_info: %\n", mb_info->vbe_mode_info);
    TERMINST().printf("vbe_mode: %\n", mb_info->vbe_mode);
    TERMINST().printf("vbe_interface_seg: %\n", mb_info->vbe_interface_seg);
    TERMINST().printf("vbe_interface_off: %\n", mb_info->vbe_interface_off);
    TERMINST().printf("vbe_interface_len: %\n", mb_info->vbe_interface_len);
  }
  else
    TERMINST().puts("-- vbe fields unavailable\n");
}
