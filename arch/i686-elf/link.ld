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
  . = 1M;
  _start = .;
  _text_start = .;
  .text : {
    *(.multiboot) /* Put the multiboot header, as it's required */
    *(.text)
  }

  . = ALIGN(4096); /* align to page size */
  _text_end = .;
  _rodata_start = .;
  .rodata : {
    *(.rodata)
  }

  . = ALIGN(4096); /* align to page size */
  _rodata_end = .;
  _data_start = .;
  .data : {
    *(.data)
  }
  
  . = ALIGN(4096); /* align to page size */
  _data_end = .;
  _bss_start = .;
  .bss : {
    bss = .;
    *(COMMON)
    *(.bss)
    *(.bootstrap_stack)
  }
  
  . = ALIGN(4096); /* align to page size */
  _bss_end = .;
  
  _end = .;
}