#ifndef AAA_MEM_H
#define AAA_MEM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

volatile void put32(addr_t addr, u32 val);
volatile u32  get32(addr_t addr);

void mem_barrier();

#ifdef __cplusplus
}
#endif /* extern C */
#endif /* AAA_MEM_H */