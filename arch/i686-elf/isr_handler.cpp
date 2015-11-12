#include "interrupts.h"
#include "register.h"
#include "terminal.h"

extern "C" void isr_handler(Registers *regs)
{
  static int count = 0;
  TERMINST().printf("unhandled interrupt: % ", regs->int_no);
  TERMINST().printf("(%)\n", count);
  TERMINST().printf("% ", regs);
  regs->printall();
  count++;
}
