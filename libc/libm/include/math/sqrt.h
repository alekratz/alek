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
f64 sqrt(num_t num)
{ return __sqrt64(static_cast<f64>(num)); }

#endif /* ALEK_LIBM_SQRT */