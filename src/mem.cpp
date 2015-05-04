#include "mem.h"

volatile void put32(void* addr, u32 val)
{
  *(volatile u32*)addr = val;
}

volatile u32  get32(void* addr)
{
  return *(volatile u32*)addr;
}

void mem_barrier()
{
  asm volatile("mov r3, #0");                   // The read register Should Be Zero before the call
  asm volatile("mcr p15, 0, r3, C7, C6, 0");    // Invalidate Entire Data Cache
  asm volatile("mcr p15, 0, r3, c7, c10, 0");   // Clean Entire Data Cache
  asm volatile("mcr p15, 0, r3, c7, c14, 0");   // Clean and Invalidate Entire Data Cache
  asm volatile("mcr p15, 0, r3, c7, c10, 4");   // Data Synchronization Barrier
  asm volatile("mcr p15, 0, r3, c7, c10, 5");   // Data Memory Barrier
}