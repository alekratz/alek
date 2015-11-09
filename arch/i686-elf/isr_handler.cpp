#include "interrupts.h"
#include "register.h"
#include "terminal.h"

void isr_handler(Registers regs)
{
  TERMINST().printf("unhandled interrupt: %", regs.int_no);
}