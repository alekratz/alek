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

#include "math/pow.h"
#include "math/sqrt.h"
#include "math/floor.h"

// TODO : refer to newlib/libm/math/e_pow.cpp
/*
 * Special cases:
 *  1.  (anything) ** 0  is 1
 *  2.  (anything) ** 1  is itself
 *  3a. (anything) ** NAN is NAN except
 *  3b. +1         ** NAN is 1
 *  4.  NAN ** (anything except 0) is NAN
 *  5.  +-(|x| > 1) **  +INF is +INF
 *  6.  +-(|x| > 1) **  -INF is +0
 *  7.  +-(|x| < 1) **  +INF is +0
 *  8.  +-(|x| < 1) **  -INF is +INF
 *  9.  +-1         ** +-INF is 1
 *  10. +0 ** (+anything except 0, NAN)               is +0
 *  11. -0 ** (+anything except 0, NAN, odd integer)  is +0
 *  12. +0 ** (-anything except 0, NAN)               is +INF
 *  13. -0 ** (-anything except 0, NAN, odd integer)  is +INF
 *  14. -0 ** (odd integer) = -( +0 ** (odd integer) )
 *  15. +INF ** (+anything except 0,NAN) is +INF
 *  16. +INF ** (-anything except 0,NAN) is +0
 *  17. -INF ** (anything)  = -0 ** (-anything)
 *  18. (-anything) ** (integer) is (-1)**(integer)*(+anything**integer)
 *  19. (-anything except 0 and inf) ** (non-integer) is NAN
 *
 * Accuracy:
 *  pow(x,y) returns x**y nearly rounded. In particular
 *      pow(integer,integer)
 *  always returns the correct integer provided it is 
 *  representable.
 *
 * Constants :
 * The hexadecimal values are the intended ones for the following 
 * constants. The decimal values may be used, provided that the 
 * compiler will convert from decimal to binary accurately enough 
 * to produce the hexadecimal values shown.
 */

f64 __pow64(f64 a, f64 b)
{
  bool gt1 = sqrt((a - 1) * (a - 1)) > 1.0;
  s32 oc = -1,
      iter = 30;
  f64 p = 1.0,
      x, x2, sum_y, sum_x;
  if(b == 0 || a == 1)
    return 1.0;
  /* integer case */
  if((b - floor(b)) == 0)
  {
    for(int i = 1; i < b; i++)
      p *= a;
  }
  /* f64 case */
  else
  {
    // TODO
  }
  return p;
}