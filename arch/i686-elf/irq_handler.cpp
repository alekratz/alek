#include "register.h"
#include "outb.h"
#include "clock.h"
#include "irq.h"

static irq_routine irq_table[16] =
{
  nullptr, nullptr, nullptr, nullptr,
  nullptr, nullptr, nullptr, nullptr, 
  nullptr, nullptr, nullptr, nullptr, 
  nullptr, nullptr, nullptr, nullptr, 
};

void register_irq_handler(u32 irq_num, irq_routine routine)
{
  irq_table[irq_num] = routine;
}

extern "C" void irq_handler(Registers *regs)
{
  irq_routine handler = irq_table[regs->int_no - 32];
  if(handler)
    handler(regs);
  // Let the slave controller know we're done, if needed
  if(regs->int_no >= 40)
    outb(0xA0, 0x20);
  // Let the master controller  know we're done
  outb(0x20, 0x20);
}