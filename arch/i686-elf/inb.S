#include "asm.h"

ENTRY(inb)
  push %ebp
  movl %esp,%ebp
  movl 8(%ebp),%edx /* port */
  xorl %eax,%eax
  inb %dx
  pop %ebp
  ret