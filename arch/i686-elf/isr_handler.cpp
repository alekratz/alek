#include "interrupts.h"
#include "register.h"
#include "terminal.h"

extern "C" void isr_handler(Registers *regs)
{
  TERMINST().printf("interrupt % called, dumping registers\n", regs->int_no);
  regs->printall();
  TERMINST().printf("halting\n");
  asm volatile("hlt");
}
