#ifndef AAA_UART_H
#define AAA_UART_H

#include "types.h"
#include "periph.h"

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

result_t uart_init();

#endif
