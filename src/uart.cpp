#include "uart.h"
#include "mem.h"
#include "cpu.h"
#include "periph.h"
#include "string.h"

#define UART0_CLKREF 3000000

static u32 calculate_divisor(u32 baud);
static u32 calculate_fraction(u32 baud);

result_t uart_init(u32 baud)
{
  // disable UART0
  P32_I(UART0::CR, 0x0);

  // begin to init GPIO pins 14 & 15
  // disable pull up/down for all GPIO pins for 150 cycles
  P32_I(GPIO_PUD, 0x0);
  cpu_delay(150);
  // disable pull up/down for pin 14 and 15 for 150 cycles
  P32_I(GPIO_PUDCLK0, (1 << 14) | (1 << 15));
  cpu_delay(150);
  // pass in 0x0 to make it take effect
  P32_I(GPIO_PUDCLK0, 0x0);

  // calculate the baud rate parts and put them in the register
  u32 divisor = calculate_divisor(baud);
  u32 fraction = calculate_fraction(baud);
  P32_I(UART0::IBRD, divisor & 0xFFFF); // get rid of the top 16 bits
  P32_I(UART0::FBRD, fraction & 0x3F); // get rid of the top 26 bits

  // enable FIFO and 8 bit data transmission (BCM 2835 datasheet, pg 184-185)
  P32_I(UART0::LCRH, (1 << 4) | (1 << 5) | (1 << 6));

  // mask all supported interrupts
  P32_I(UART0::IMSC, 
    UART0IntMasks::CTSMIM | UART0IntMasks::RXIM | UART0IntMasks::TXIM | 
    UART0IntMasks::RTIM | UART0IntMasks::FEIM | UART0IntMasks::PEIM | 
    UART0IntMasks::BEIM | UART0IntMasks::OEIM);

  // enable UART0, receive and transfer part
  P32_I(UART0::CR, (1 << 0) | (1 << 7) | (1 << 8));
  return R_OK;
}

void uart_putc(char c)
{
  while(G32_I(UART0::FR) & UART0FRMasks::TXFF);
  P32_I(UART0::DR, c);
}

char uart_getc()
{
  while(G32_I(UART0::FR) & UART0FRMasks::RXFE);
  return G32_I(UART0::DR);
}

void uart_write(const char* buf, size_t sz)
{
  for(size_t i = 0; i < sz; i++)
    uart_putc(buf[i]);
}

void uart_puts(const char* buf)
{
  uart_write(buf, strlen(buf));
}

static u32 calculate_divisor(u32 baud)
{
  // divisor is going to be clock rate / (16 * baud)
  return UART0_CLKREF / (16 * baud);
}

static u32 calculate_fraction(u32 baud)
{
  float divisor = static_cast<float>(UART0_CLKREF) / (16.0 * static_cast<float>(baud));
  while(divisor >= 1) divisor--;
  return static_cast<u32>((divisor * 64) + 0.5);
}
