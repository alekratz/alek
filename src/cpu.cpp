#include "cpu.h"

volatile void cpu_delay(u32 count)
{
  asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
   : : [count]"r"(count) : "cc");
}