#ifndef ALEK_LIBM_LOG_H
#define ALEK_LIBM_LOG_H

#include <types.h>

/**
 * Red Hat's newlib libm implementation of ln(x) for doubles.
 * This is useful for copying/stealing
 */
f64 __ieee754_log(f64 x);

#define LN(x) (__ieee754_log(x))

template <typename num_t>
num_t logbase(num_t num, num_t base)
{ return LN(static_cast<f64>(num)) / LN(static_cast<f64>(base)); }

#define log2(x) (logbase(x, 2))
#define log10(x) (logbase(x, 10))
#define ln(x) LN(x)

#endif