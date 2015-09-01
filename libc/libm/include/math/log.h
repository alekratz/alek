/*
 * Copyright (C) 2015 Alek Ratzloff
 *
 * This file is part of Alek's Little Endian Kernel.
 * 
 * Alek's Little Endian Kernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Alek's Little Endian Kernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Alek's Little Endian Kernel.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ALEK_LIBM_LOG_H
#define ALEK_LIBM_LOG_H

#include <types.h>

/**
 * Red Hat's newlib libm implementation of ln(x) for doubles.
 * This is useful for copying/stealing
 */
extern "C" f64 __ieee754_log64(f64 x);

#define LN(x) (__ieee754_log64(x))

template <typename num_t>
f64 logbase(num_t num, num_t base)
{ return LN(static_cast<f64>(num)) / LN(static_cast<f64>(base)); }

#define log2(x) (logbase(x, 2))
#define log10(x) (logbase(x, 10))
#define ln(x) LN(x)

#endif