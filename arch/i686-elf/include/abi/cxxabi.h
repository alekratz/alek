#ifndef ALEK_CXX_CXX_ABI_H
#define ALEK_CXX_CXX_ABI_H

#include "types.h"
namespace __cxxabiv1 {

extern "C" {

// for more info:
// https://mentorembedded.github.io/cxx-abi/abi.html#dso-dtor-runtime-api

s32 __cxa_atexit(void (*dtor) (addr_t), addr_t arg, addr_t dso);
void __cxa_finalize(addr_t f);

} /* extern "C" */
} /* namespace __cxxabiv1 */
#endif /* ALEK_CXX_CXX_ABI_H */