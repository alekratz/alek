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

#include "asm.h"

#define IRQ_COMMON_STUB(x) \
  pusha ; \
  push %ds ; \
  push %es ; \
  push %fs ; \
  push %gs ; \
  mov $0x10,%ax ; \
  mov %ax,%ds ; \
  mov %ax,%es ; \
  mov %ax,%fs ; \
  mov %ax,%gs ; \
  mov %esp,%eax ; \
  push %eax ; \
  leal irq_handler,%eax ; \
  call *%eax ; \
  pop %eax ; \
  pop %gs ; \
  pop %fs ; \
  pop %es ; \
  pop %ds ; \
  popa ; \
  add $0x8,%esp ; \
  iret

#define IRQ(x) \
  ENTRY(irq ## x) ; \
  cli ; \
  pushl $0 ; \
  pushl $(x+32) ; \
  IRQ_COMMON_STUB(x)

IRQ(0)
IRQ(1)
IRQ(2)
IRQ(3)
IRQ(4)
IRQ(5)
IRQ(6)
IRQ(7)
IRQ(8)
IRQ(9)
IRQ(10)
IRQ(11)
IRQ(12)
IRQ(13)
IRQ(14)
IRQ(15)
