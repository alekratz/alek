#include "gpu.h"
#include "uart.h"

static FramebufferInfo d_fb_info; // forever version of framebufferinfo

extern "C" void kmain()
{

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

}