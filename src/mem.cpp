#include "mem.h"

void put32(void* addr, u32 val)
{
  *(volatile u32*)addr = val;
}

u32  get32(void* addr)
{
  return *(volatile u32*)addr;
}