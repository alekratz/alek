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

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "asm.h"

/*ENTRY(gdt_flush):*/
.text
.align 16
.globl gdt_flush
.type gdt_flush,@function
gdt_flush:
  push %ebp
  mov %esp, %ebp

  mov 8(%ebp), %eax /* move the first arg into the eax register */
  lgdt (%eax) /* load descriptor table */

  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss

  jmp 0f /* far jump */
0:
  pop %ebp
  ret
