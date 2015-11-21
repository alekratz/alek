#ifndef ALEK_IRQ_H
#define ALEK_IRQ_H

typedef void (*irq_routine)(Registers *regs);
void register_irq_handler(u32 irq_num, irq_routine routine);

#endif