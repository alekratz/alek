#include "gpu.h"
#include "uart.h"

extern "C" void kmain()
{
  uart_init();
  framebuffer_init();

  // draw some stuff
  

  while(1);
}