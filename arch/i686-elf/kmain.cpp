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

#include <version.h>
#include <sizes.h>
#include <types.h>

// Number of threads we're going to be running for now
#define THREAD_COUNT 4
// Minimum memory required (kb)
#define MIN_MEM 1024_kb

#define LOGO \
"      db      `7MMF'      `7MM\"\"\"YMM  `7MMF' `YMM' \n" \
"     ;MM:       MM          MM    `7    MM   .M'   \n" \
"    ,V^MM.      MM          MM   d      MM .d\"     \n" \
"   ,M  `MM      MM          MMmmMM      MMMMM.     \n" \
"   AbmmmqMA     MM      ,   MM   Y  ,   MM  VMA    \n" \
"  A'     VML    MM     ,M   MM     ,M   MM   `MM.  \n" \
".AMA.   .AMMA..JMMmmmmMMM .JMMmmmmMMM .JMML.   MMb.\n"

extern void init_gdt();
extern void init_idt();

extern "C"
{

  void halt()
  {
    asm volatile("hlt");
  }

  void kmain(u32 eax, MBInfo* mb_info)
  {
    if(eax != 0x2BADB002)
      halt();

    // Init descriptor tables (GDT and IDT)
    init_gdt();
    init_idt();

    TERMINST().clear();
    TERMINST().printf(LOGO);
    TERMINST().printf("Alek's Little Endian Kernel " VERSION_STR "\n");
    //debug_flag_info(mb_info);

    size_t mem_total = mb_info->mem_upper - mb_info->mem_lower;
    // make sure it's at least 1MB
    if(mem_total < MIN_MEM)
    {
      TERMINST().printf("error: I need at least % kb of memory to run\n", static_cast<u64>(MIN_MEM.as<kb>()));
      TERMINST().printf("I found % kb of usable memory\n", mem_total);
      halt();
    }

    TERMINST().printf("Available memory for me: % kb\n", mem_total);

    // Divy up the memory
    size_t stack_size = mem_total / THREAD_COUNT;
    TERMINST().printf("I have the capability to run % threads\n", THREAD_COUNT);
    TERMINST().printf("Using stack size of % kb\n", stack_size);

    // let's play the divide by zero game
    TERMINST().printf("Dividing by zero...");
    int k = 1 / 0;

    for(s32 i = 0; i < THREAD_COUNT; i++)
    {
    }

    while(1);
  }
}
