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

#include <types.h>

// Number of threads we're going to be running for now
#define THREAD_COUNT 8
// Minimum memory required (kb)
#define MIN_MEM 1024 

extern "C"
{

  void halt()
  {
    TERMINST().printf("HALTING");
    while(1);
  }

  void kmain(u32 eax, MBInfo* mb_info)
  {
    if(eax != 0x2BADB002)
    {
      TERMINST().printf("Invalid multiboot EAX value: %\n", eax);
      halt();
    }

    debug_flag_info(mb_info);

    size_t mem_total = mb_info->mem_upper - mb_info->mem_lower;
    // make sure it's at least 1MB
    if(mem_total < MIN_MEM)
    {
      TERMINST().printf("error: I need at least % kb of memory to run", MIN_MEM);
      halt();
    }

    TERMINST().printf("Available memory for me: % kb\n", mem_total);

    // Divy up the memory
    size_t stack_size = mem_total / THREAD_COUNT;
    TERMINST().printf("Using stack size of % kb", stack_size);

    for(s32 i = 0; i < THREAD_COUNT; i++)
    {
    }

    while(1);
  }
}
