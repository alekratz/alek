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

#define ASM_FILE 1
/* Constants used for creating a multiboot header */
.set ALIGN,   1 << 0              /* align loaded modules on page boundaries */
.set MEMINFO, 1 << 1              /* provide memory map */
.set FLAGS,   ALIGN | MEMINFO     /* multiboot 'flag' field */
.set MAGIC,   0x1BADB002          /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS)   /* checksum of above */

/* Multiboot header */
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
header_addr:
.long 0
load_addr:
.long 0
load_end_addr:
.long 0
bss_end_addr:
.long 0
entry_addr:
.long 0

/* Set up the stack */
.section bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 /* 16 KB */
stack_top:

/* text section */
.section .text
.global start
.type start, @function
start:
  /* Set %esp */
  movl $stack_top, %esp
  push entry_addr
  push bss_end_addr
  push load_end_addr
  push load_addr
  push header_addr
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
