#ifndef ALEK_LIBM_SQRT
#define ALEK_LIBM_SQRT

#include <types.h>

/**
 * Architecture implemented square root
 */
extern "C" f64 __sqrt64(f64 num);

/**
 * "Lazy" version of square root
 */
template<typename num_t>
num_t sqrt(num_t num)
{ return __sqrt64(static_cast<f64>(num)); }

#endif /* ALEK_LIBM_SQRT */