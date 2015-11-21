#include "asm.h"

#define IRQ_COMMON_STUB(x) \
  pusha ; \
  push %ds ; \
  push %es ; \
  push %fs ; \
  push %gs ; \
  mov $0x10,%ax ; \
  mov %ax,%ds ; \
  mov %ax,%es ; \
  mov %ax,%fs ; \
  mov %ax,%gs ; \
  mov %esp,%eax ; \
  push %eax ; \
  leal irq ## x ## _handler,%eax ; \
  call *%eax ; \
  pop %eax ; \
  pop %gs ; \
  pop %fs ; \
  pop %es ; \
  pop %ds ; \
  popa ; \
  add $0x8,%esp ; \
  iret

#define IRQ(x) \
  ENTRY(irq ## x) ; \
  cli ; \
  pushl $0 ; \
  pushl x ; \
  IRQ_COMMON_STUB(x)

IRQ(0)
IRQ(1)
IRQ(2)
IRQ(3)
IRQ(4)
IRQ(5)
IRQ(6)
IRQ(7)
IRQ(8)
IRQ(9)
IRQ(10)
IRQ(11)
IRQ(12)
IRQ(13)
IRQ(14)
IRQ(15)
