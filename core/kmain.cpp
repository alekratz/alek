/*
 * Copyright (C) 2015 Alek Ratzloff
 *
 * This file is part of Alek's Awesome Arm Kernel.
 * 
 * Alek's Awesome Arm Kernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Alek's Awesome Arm Kernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Alek's Awesome Arm Kernel.  If not, see <http://www.gnu.org/licenses/>.
 */

#if defined(ARM)
#include "gpu.h"
#include "uart.h"

static FramebufferInfo d_fb_info; // forever version of framebufferinfo
#endif

extern "C" void kmain()
{

#if defined(ARM)
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
#elif defined(I686)
  while(1);
#endif
}