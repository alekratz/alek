#ifndef ALEK_LIBM_FLOOR_H
#define ALEK_LIBM_FLOOR_H

#include <types.h>

extern "C" f64 __floor64(f64 num);

template<typename num_t>
f64 floor(num_t num)
{ return __floor64(static_cast<f64>(num)); }

#endif