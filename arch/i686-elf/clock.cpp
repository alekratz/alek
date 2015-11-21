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
#include <kernel.h>
#include <types.h>
#include "clock.h"
#include "cpu_io.h"
#include "register.h"
#include "terminal.h"
#include "irq.h"

static u16 clock_ticks = 0;
static void clock_handler(Registers *regs);

// kernel.h
extern "C" void set_clock_hz(u16 hz)
{
  u16 divisor = 1193180 / hz;
  outb(0x43, 0x36); // command mode
  outb(0x40, divisor & 0xFF);
  outb(0x40, (divisor >> 8) & 0xFF);
}

void init_clock()
{
  // set_clock_hz(100);
  register_irq_handler(0, clock_handler);
}

static void clock_handler(Registers *regs)
{
  clock_ticks++;
  //if(clock_ticks % 18 == 0)
  //  TERMINST().println("One second has passed");
  // TODO : fun clock things here
}