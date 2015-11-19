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

#define KERN_HEAP_SIZE 16384
#define KERN_STACK_SIZE 16384

#define ASM_FILE 1
/* Constants used for creating a multiboot header */
.set ALIGN,   1 << 0              /* align loaded modules on page boundaries */
.set MEMINFO, 1 << 1              /* provide memory map */
.set FLAGS,   ALIGN               /* multiboot 'flag' field */
.set MAGIC,   0x1BADB002          /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS)   /* checksum of above */

/* Multiboot header */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

/* Set up the stack */
.section bootstrap_stack, "aw", @nobits
kern_heap_info_start:
.skip KERN_HEAP_SIZE * 16 / 1024 /* 16 * 16 KB */
kern_heap_info_end:

kern_heap_start:
.skip KERN_HEAP_SIZE /* 16 KB */
kern_heap_end:

kern_stack_bottom:
.skip KERN_STACK_SIZE /* 16 KB */
kern_stack_top:

/* export the heap start and stack bottom */
.globl kern_heap_start
.globl kern_stack_top
.globl kern_heap_info_end
.globl kern_heap_info_start

/* text section */
.section .text
.global start
.type start, @function
start:
  /* Do this to make DOS processors happy */
  finit
  /* Set %esp */
  movl $kern_stack_top, %esp
  movl %esp, %ebp
  
  push %ebx
  push %eax

  /* Jump into the kernel */
  call kmain
  /* After the kernel exits, be sure to call __cxa_finalize */
  push 0
  call __cxa_finalize

  /* Hang */
  cli
  hlt
.Lhang:
  jmp .Lhang

.section .text
kern_heap_size: .long KERN_HEAP_SIZE
kern_stack_size: .long KERN_STACK_SIZE

.globl kern_heap_size
.globl kern_stack_size