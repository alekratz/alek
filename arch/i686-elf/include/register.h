#ifndef ALEK_REGISTER_H
#define ALEK_REGISTER_H

#include <types.h>

struct Registers
{
  u32 ds;   // data segment selector
  u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; // pushed by pusha
  u32 int_no, err_code;  // interrupt number and error code if applicable
  u32 eip, cs, eflags, useresp, ss; // pushed by the CPU
};

#endif