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
#include "mboot.h"
#include "descriptor_tables.h"
#include "clock.h"
#include "keyboard.h"

#include <version.h>
#include <sizes.h>
#include <types.h>
#include <heap.h>
#include <kernel.h>

// Number of threads we're going to be running for now
#define THREAD_COUNT 4
// Minimum memory required (kb)
#define MIN_MEM 5120_kb

#define LOGO \
"      db      `7MMF'      `7MM\"\"\"YMM  `7MMF' `YMM' \n" \
"     ;MM:       MM          MM    `7    MM   .M'   \n" \
"    ,V^MM.      MM          MM   d      MM .d\"     \n" \
"   ,M  `MM      MM          MMmmMM      MMMMM.     \n" \
"   AbmmmqMA     MM      ,   MM   Y  ,   MM  VMA    \n" \
"  A'     VML    MM     ,M   MM     ,M   MM   `MM.  \n" \
".AMA.   .AMMA..JMMmmmmMMM .JMMmmmmMMM .JMML.   MMb.\n"

extern "C"
{

  void halt()
  {
    asm volatile("hlt");
  }

  void panic(const char *reason)
  {
    TERMINST().println("Kernel panicked: ", reason);
    halt();
  }

  void kmain(u32 eax, MBInfo* mb_info)
  {
    if(eax != 0x2BADB002)
      halt();

    // Init descriptor tables (GDT and IDT)
    init_gdt();
    init_idt();
    init_irq();
    init_clock();
    init_keyboard();
    init_kheap();
    asm volatile("sti");

    TERMINST().clear();
    TERMINST().println(LOGO);
    TERMINST().println("Alek's Little Endian Kernel " VERSION_STR);
    TERMINST().println("ALEK is ready to roll.");
    //debug_flag_info(mb_info);

    size_t mem_total = mb_info->mem_upper - mb_info->mem_lower;
    // make sure it's at least 1MB
    if(mem_total < MIN_MEM)
    {
      TERMINST().println("error: I need at least ", static_cast<u64>(MIN_MEM.as<kb>()), " kb of memory to run");
      TERMINST().println("I found ", mem_total, " kb of usable memory");
      halt();
    }

    TERMINST().println("mem avail: ", mem_total, " kb");

    // Divy up the memory
    size_t mem_size = mem_total / THREAD_COUNT;

    while(1);
  }
}

