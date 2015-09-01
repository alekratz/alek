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

#include "terminal.h"
extern "C"
{

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
    u32 mmap_addr;
    u32 mmap_length;
  };

  void halt()
  {
    while(1);
  }

  void kmain(u32 eax, MBInfo* mb_info)
  {
    Terminal& term_inst = Terminal::get_instance();
    if(eax != 0x2BADB002)
    {
      term_inst.printf("Invalid multiboot EAX value: %X\n", eax);
      halt();
    }
    
    term_inst.printf("flags: %x\n", mb_info->flags);
    term_inst.printf("mem_lower: %x\n", mb_info->mem_lower);
    term_inst.printf("mem_upper: %x\n", mb_info->mem_upper);
    term_inst.printf("boot_device: %x\n", mb_info->boot_device);
    term_inst.printf("cmdline: ");
    term_inst.puts(mb_info->cmdline);
    term_inst.putc('\n');
    term_inst.printf("mods_count: %x\n", mb_info->mods_count);
    term_inst.printf("mods_addr: %x\n", mb_info->mods_addr);
    //term_inst.printf("syms: %x\n", syms[mb_info->8]);
    term_inst.printf("mmap_addr: %x\n", mb_info->mmap_addr);
    term_inst.printf("mmap_length: %x\n", mb_info->mmap_length);

    while(1);
  }
}