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
  Terminal& term_inst = Terminal::get_instance();
  term_inst.printf("flags: %\n", mb_info->flags);

  if(HAS_FLAG(mb_info->flags, MBOOT_MEM))
  {
    term_inst.printf("mem_lower: %\n", mb_info->mem_lower * 1024);
    term_inst.printf("mem_upper: %\n", mb_info->mem_upper * 1024);
  }
  else
  {
    term_inst.puts("-- mem fields unavailable\n");
  }
  if(HAS_FLAG(mb_info->flags, MBOOT_BOOTDEV))
    term_inst.printf("boot_device: %\n", mb_info->boot_device);
  else
  {
    term_inst.puts("-- boot_device field unavailable\n");
  }
  if(HAS_FLAG(mb_info->flags, MBOOT_CMDLINE))
    term_inst.printf("cmdline: %\n", mb_info->cmdline);
  else
  {
    term_inst.puts("-- cmdline field unavailable\n");
  }
  if(HAS_FLAG(mb_info->flags, MBOOT_MODS))
  {
    term_inst.printf("mods_count: %\n", mb_info->mods_count);
    term_inst.printf("mods_addr: %\n", mb_info->mods_addr);
  }
  else
  {
    term_inst.puts("-- mods fields unavailable\n");
  }
  //term_inst.printf("syms: %\n", syms[mb_info->8]);
  if(HAS_FLAG(mb_info->flags, MBOOT_MMAP))
  {
    term_inst.printf("mmap_addr: %\n", mb_info->mmap_addr);
    term_inst.printf("mmap_length: %\n", mb_info->mmap_length);
  }
  else
  {
    term_inst.puts("-- mmap fields unavailable\n");
  }

  if(HAS_FLAG(mb_info->flags, MBOOT_DRIVES))
  {
    term_inst.printf("drives_length: %\n", mb_info->drives_length);
    term_inst.printf("drives_addr: %\n", mb_info->drives_addr);
  }
  else
    term_inst.puts("-- drives fields unavailable\n");

  if(HAS_FLAG(mb_info->flags, MBOOT_CONFIG_TABLE))
    term_inst.printf("config_table: %\n", mb_info->config_table);
  else
    term_inst.puts("-- config table field unavailable\n");

  if(HAS_FLAG(mb_info->flags, MBOOT_BOOT_LOADER_NAME))
    term_inst.printf("boot_loader_name: %\n", mb_info->boot_loader_name);
  else
    term_inst.puts("-- boot loader name field unavailable\n");

  if(HAS_FLAG(mb_info->flags, MBOOT_APM_TABLE))
    term_inst.printf("apm_table: %\n", mb_info->apm_table);
  else
    term_inst.puts("-- apm table field unavailable\n");

  if(HAS_FLAG(mb_info->flags, MBOOT_VBE))
  {
    term_inst.printf("vbe_control_info: %\n", mb_info->vbe_control_info);
    term_inst.printf("vbe_mode_info: %\n", mb_info->vbe_mode_info);
    term_inst.printf("vbe_mode: %\n", mb_info->vbe_mode);
    term_inst.printf("vbe_interface_seg: %\n", mb_info->vbe_interface_seg);
    term_inst.printf("vbe_interface_off: %\n", mb_info->vbe_interface_off);
    term_inst.printf("vbe_interface_len: %\n", mb_info->vbe_interface_len);
  }
  else
    term_inst.puts("-- vbe fields unavailable\n");
}
