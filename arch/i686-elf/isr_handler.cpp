#include "interrupts.h"
#include "register.h"
#include "terminal.h"

extern "C" void isr_handler(Registers *regs)
{
  TERMINST().println("interrupt ", regs->int_no, " called, dumping registers");
  regs->printall();
  TERMINST().println("halting");
  asm volatile("hlt");
}
