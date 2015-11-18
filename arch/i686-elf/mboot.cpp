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
  TERMINST().println("flags: ", mb_info->flags);

  if(HAS_FLAG(mb_info->flags, MBOOT_MEM))
  {
    TERMINST().println("mem_lower: ", mb_info->mem_lower, "kb");
    TERMINST().println("mem_upper: ", mb_info->mem_upper, "kb");
  }
  else
  {
    TERMINST().println("-- mem fields unavailable");
  }
  if(HAS_FLAG(mb_info->flags, MBOOT_BOOTDEV))
    TERMINST().println("boot_device: ", mb_info->boot_device);
  else
  {
    TERMINST().println("-- boot_device field unavailable");
  }
  if(HAS_FLAG(mb_info->flags, MBOOT_CMDLINE))
    TERMINST().println("cmdline: ", mb_info->cmdline);
  else
  {
    TERMINST().println("-- cmdline field unavailable");
  }
  if(HAS_FLAG(mb_info->flags, MBOOT_MODS))
  {
    TERMINST().println("mods_count: ", mb_info->mods_count);
    TERMINST().println("mods_addr: ", mb_info->mods_addr);
  }
  else
  {
    TERMINST().println("-- mods fields unavailable");
  }

  if(HAS_FLAG(mb_info->flags, MBOOT_MMAP))
  {
    TERMINST().println("mmap_addr: ", mb_info->mmap_addr);
    TERMINST().println("mmap_length: ", mb_info->mmap_length);
  }
  else
  {
    TERMINST().println("-- mmap fields unavailable");
  }

  if(HAS_FLAG(mb_info->flags, MBOOT_DRIVES))
  {
    TERMINST().println("drives_length: ", mb_info->drives_length);
    TERMINST().println("drives_addr: ", mb_info->drives_addr);
  }
  else
    TERMINST().println("-- drives fields unavailable");

  if(HAS_FLAG(mb_info->flags, MBOOT_CONFIG_TABLE))
    TERMINST().println("config_table: ", mb_info->config_table);
  else
    TERMINST().println("-- config table field unavailable");

  if(HAS_FLAG(mb_info->flags, MBOOT_BOOT_LOADER_NAME))
    TERMINST().println("boot_loader_name: ", mb_info->boot_loader_name);
  else
    TERMINST().println("-- boot loader name field unavailable");

  if(HAS_FLAG(mb_info->flags, MBOOT_APM_TABLE))
    TERMINST().println("apm_table: ", mb_info->apm_table);
  else
    TERMINST().println("-- apm table field unavailable");

  if(HAS_FLAG(mb_info->flags, MBOOT_VBE))
  {
    TERMINST().println("vbe_control_info: ", mb_info->vbe_control_info);
    TERMINST().println("vbe_mode_info: ", mb_info->vbe_mode_info);
    TERMINST().println("vbe_mode: ", mb_info->vbe_mode);
    TERMINST().println("vbe_interface_seg: ", mb_info->vbe_interface_seg);
    TERMINST().println("vbe_interface_off: ", mb_info->vbe_interface_off);
    TERMINST().println("vbe_interface_len: ", mb_info->vbe_interface_len);
  }
  else
    TERMINST().println("-- vbe fields unavailable");
}
