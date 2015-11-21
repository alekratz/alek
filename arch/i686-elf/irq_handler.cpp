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

#include "register.h"
#include "cpu_io.h"
#include "clock.h"
#include "irq.h"

static irq_routine irq_table[16] =
{
  nullptr, nullptr, nullptr, nullptr,
  nullptr, nullptr, nullptr, nullptr, 
  nullptr, nullptr, nullptr, nullptr, 
  nullptr, nullptr, nullptr, nullptr, 
};

void register_irq_handler(u32 irq_num, irq_routine routine)
{
  irq_table[irq_num] = routine;
}

extern "C" void irq_handler(Registers *regs)
{
  irq_routine handler = irq_table[regs->int_no - 32];
  if(handler)
    handler(regs);
  // Let the slave controller know we're done, if needed
  if(regs->int_no >= 40)
    outb(0xA0, 0x20);
  // Let the master controller  know we're done
  outb(0x20, 0x20);
}