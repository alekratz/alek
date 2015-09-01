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

extern "C" struct mem_fields
{
  u32 *header_addr;
  u32 *load_addr;
  u32 *load_end_addr;
  u32 *bss_end_addr;
  u32 *entry_addr;
};

extern "C" void kmain(struct mem_fields mem)
{
  Terminal& term_inst = Terminal::get_instance();
  term_inst.printf("header_addr:   0x%p\n", mem.header_addr);
  term_inst.printf("load_addr:     0x%p\n", mem.load_addr);
  term_inst.printf("load_end_addr: 0x%p\n", mem.load_end_addr);
  term_inst.printf("bss_end_addr:  0x%p\n", mem.bss_end_addr);
  term_inst.printf("entry_addr:    0x%p\n", mem.entry_addr);
  while(1);
}