#include "register.h"
#include "outb.h"
#include "clock.h"

extern "C" {

void irq0_handler(Registers* regs)
{
  clock_handler(regs);
}

void irq1_handler(Registers* regs)
{

}

void irq2_handler(Registers* regs)
{

}

void irq3_handler(Registers* regs)
{

}

void irq4_handler(Registers* regs)
{

}

void irq5_handler(Registers* regs)
{

}

void irq6_handler(Registers* regs)
{

}

void irq7_handler(Registers* regs)
{

}

void irq8_handler(Registers* regs)
{

}

void irq9_handler(Registers* regs)
{

}

void irq10_handler(Registers* regs)
{

}

void irq11_handler(Registers* regs)
{

}

void irq12_handler(Registers* regs)
{

}

void irq13_handler(Registers* regs)
{

}

void irq14_handler(Registers* regs)
{

}

void irq15_handler(Registers* regs)
{

}

}