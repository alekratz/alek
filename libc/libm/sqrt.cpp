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

#include "math/sqrt.h"

/**
 * Actual implementation of the square root function by the architecture
 * Hopefully works super fast!
 */
static f64 __arch_sqrt64(f64 num);
/**
 * Hacky implementation of the sqrt() for ARM
 */
#ifdef __arm__
static f32 __arch_sqrt32(f32 num);
#endif

f64 __sqrt64(f64 num)
{
  return __arch_sqrt64(num);
}

static f64 __arch_sqrt64(f64 num)
{
  f64 out = 0;
#if defined(__i386) || defined(__x86_64__)
  asm("fldl %[input]   ;"
      "fsqrt           ;"
      "fstl %[output]  ;"
      : [output] "=m" (out)
      : [input] "m"   (num)
    );
#else
#ifdef __arm__
  /*
  asm("vldr.64 d6, %1  ;"
      "vsqrt.f64 %[output], %[input] ;"
      "vstr.64 d7 [%0] ;"
      : [output] "=w" (out)
      : [input] "w"  (num)
    );
    */
  // FIXME : figure out how to get the inline asm working on this one
  // if you plug in the "w" constraints, it still replaces them with the
  // 32 bit registers and complains. So NOBODY gets a happy square root implementation
  out = __arch_sqrt32(static_cast<f32>(num));
#endif
#endif
  return out;
}

f32 __arch_sqrt32(f32 num)
{
  f32 out = 0.0;
#ifdef __x86_64__
  asm("fldl %[input]   ;"
      "fsqrt           ;"
      "fstl %[output]  ;"
      : [output] "=r" (out)
      : [input] "r"   (num)
    );
#else
#ifdef __arm__
  asm(/*"vldr.64 d6, %1  ;"*/
      "vsqrt.f32 %[output], %[input] ;"
      /*"vstr.64 d7 [%0] ;"*/
      : [output] "=t" (out)
      : [input] "t"  (num)
    );
#endif
#endif
  return out;
}