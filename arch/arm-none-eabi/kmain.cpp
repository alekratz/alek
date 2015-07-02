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
 
#include "gpu.h"
#include "uart.h"
#include <mem.h>

static FramebufferInfo d_fb_info; // forever version of framebufferinfo

#define GPFSEL1 ((addr_t)0x20200004)
#define GPSET0  ((addr_t)0x2020001C)
#define GPCLR0  ((addr_t)0x20200028)

void dummy() { return; }

extern "C" void kmain()
{
  u32 ra = get32(GPFSEL1);
  ra &= ~(7 << 18);
  ra |= 1 << 18;
  put32(GPFSEL1, ra);

  while(1)
  {
    put32(GPSET0, 1 << 16);
    for(ra = 0; ra < 0x100000; ra++)
      dummy();
    put32(GPCLR0, 1 << 16);
    for(ra = 0; ra < 0x100000; ra++)
      dummy();
  } 
  /*
  // initialize uart, and specifically, serial communication
  uart_init(115200);
  // initialize the framebuffer
  //framebuffer_init(&d_fb_info);
  // draw some stuff
  
  uart_puts("Hello, from Kernel land!\r\n");
  uart_puts("echo:\r\n");
  
  while(1)
  {
    uart_putc(uart_getc());
  }
  */
}