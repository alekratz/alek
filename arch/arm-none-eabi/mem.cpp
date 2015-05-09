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

#include "mem.h"

void mem_barrier()
{
  asm volatile("mov r3, #0");                   // The read register Should Be Zero before the call
  asm volatile("mcr p15, 0, r3, C7, C6, 0");    // Invalidate Entire Data Cache
  asm volatile("mcr p15, 0, r3, c7, c10, 0");   // Clean Entire Data Cache
  asm volatile("mcr p15, 0, r3, c7, c14, 0");   // Clean and Invalidate Entire Data Cache
  asm volatile("mcr p15, 0, r3, c7, c10, 4");   // Data Synchronization Barrier
  asm volatile("mcr p15, 0, r3, c7, c10, 5");   // Data Memory Barrier
}