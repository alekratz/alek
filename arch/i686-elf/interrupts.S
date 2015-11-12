#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "asm.h"

isr_stub:
  pusha
  push %ds
  push %es
  push %fs
  push %gs
  mov $0x10,%ax  /* load kernel ds */
  mov %ax,%ds
  mov %ax,%es
  mov %ax,%fs
  mov %ax,%gs
  movl %esp,%eax
  pushl %eax
  leal isr_handler,%eax
  call %eax /* this call preserves the eip */
  popl %eax
  pop %gs
  pop %fs
  pop %es
  pop %ds
  popa
  add %esp,8
  sti
  iret

/* macro for defining ISRs that have no error code */
#define ISR_NOERR(n) \
ENTRY(isr ## n)   \
  cli           ; \
  push $0      ; \
  push $n      ; \
  jmp isr_stub  ;

/* macro for defining ISRs that have do have an error code; this is pushed automatically for us */
#define ISR_WITHERR(n) \
ENTRY(isr ## n)\
  cli           ;\
  push $n       ;\
  jmp isr_stub  ;

ISR_NOERR(0)
ISR_NOERR(1)
ISR_NOERR(2)
ISR_NOERR(3)
ISR_NOERR(4)
ISR_NOERR(5)
ISR_NOERR(6)
ISR_NOERR(7)
ISR_WITHERR(8)
ISR_NOERR(9)
ISR_WITHERR(10)
ISR_WITHERR(11)
ISR_WITHERR(12)
ISR_WITHERR(13)
ISR_WITHERR(14)
ISR_NOERR(15)
ISR_NOERR(16)
ISR_NOERR(17)
ISR_NOERR(18)
ISR_NOERR(19)
ISR_NOERR(20)
ISR_NOERR(21)
ISR_NOERR(22)
ISR_NOERR(23)
ISR_NOERR(24)
ISR_NOERR(25)
ISR_NOERR(26)
ISR_NOERR(27)
ISR_NOERR(28)
ISR_NOERR(29)
ISR_NOERR(30)
ISR_NOERR(31)