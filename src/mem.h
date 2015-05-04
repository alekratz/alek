#ifndef MEM_H
#define MEM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

void put32(void* addr, u32 val);
u32  get32(void* addr);

#ifdef __cplusplus
}
#endif
#endif