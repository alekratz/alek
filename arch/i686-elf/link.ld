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

ENTRY(start)

SECTIONS
{
  /* Typical place for bootloaders to load a kernel up. */
  . = 0x100000;

  .text BLOCK(4K) : ALIGN(4K) 
  {
    *(.multiboot)
    *(.text)
  }

  .rodata BLOCK(4K) : ALIGN(4K) 
  {
    *(.rodata)
  }

  .data BLOCK(4K) : ALIGN(4K) 
  {
    *(.data)
  }
  
  .bss BLOCK(4K) : ALIGN(4K) 
  {
    *(COMMON)
    *(.bss)
    *(.bootstrap_stack)
  }
  
}