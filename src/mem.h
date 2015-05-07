#ifndef AAA_MEM_H
#define AAA_MEM_H

#include "types.h"

volatile void put32(addr_t addr, u32 val);
volatile u32  get32(addr_t addr);

/**
 * puts a 32 bit integer
 */
#define P32_I(addr, val) put32(reinterpret_cast<addr_t>(addr), val)
#define G32_I(addr) get32(reinterpret_cast<addr_t>(addr))

void mem_barrier();

#endif /* AAA_MEM_H */
