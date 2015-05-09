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

#ifndef AAA_UART_H
#define AAA_UART_H

#include <types.h>
#include <periph.h>

enum UART0
{
  Base    = GPIO_BASE + 0x1000,
  DR      = Base + 0x00,
  RSRECR  = Base + 0x04,
  FR      = Base + 0x18,
  ILPR    = Base + 0x20,
  IBRD    = Base + 0x24,
  FBRD    = Base + 0x28,
  LCRH    = Base + 0x2C,
  CR      = Base + 0x30,
  IFLS    = Base + 0x34,
  IMSC    = Base + 0x38,
  RIS     = Base + 0x3C,
  MIS     = Base + 0x40,
  ICR     = Base + 0x44,
  DMACR   = Base + 0x48,
  ITCR    = Base + 0x80,
  ITIP    = Base + 0x84,
  ITOP    = Base + 0x88,
  TDR     = Base + 0x8C
};

enum UART0FRMasks
{
  TXFE = 1 << 7,      // Transmit FIFO empty
  RXFF = 1 << 6,      // Receive FIFO full
  TXFF = 1 << 5,      // Transmit FIFO full
  RXFE = 1 << 4,      // Receive FIFO empty
  BUSY = 1 << 3       // UART device is busy transmitting data
};

enum UART0IntMasks
{
  OEIM    = 1 << 10,  // Overrun error interrupt mask
  BEIM    = 1 << 9,   // Break error interrupt mask
  PEIM    = 1 << 8,   // Parity error interrupt mask
  FEIM    = 1 << 7,   // Framing error interrupt mask
  RTIM    = 1 << 6,   // Receive timeout interrupt mask
  TXIM    = 1 << 5,   // Transmit interrupt mask
  RXIM    = 1 << 4,   // Receive interrupt mask
  CTSMIM  = 1 << 1    // nUARTCTS modem interrupt mask
};

result_t uart_init(u32 baud);
void uart_putc(char c);
char uart_getc();
void uart_write(const char* buf, size_t sz);
void uart_puts(const char* buf);

#endif
