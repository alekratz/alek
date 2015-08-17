#include "math/floor.h"

f64 __floor64(f64 in)
{
  /**
   * TODO : number validation to make sure it's not NaN, return for infinity, etc
   */
#ifdef __i386
   s64 out;
   asm("fld %[input]    ;"
       "fistp %[output] ;"
       : [output] "=m" (out)
       : [input]  "r"  (in)
    );
   return static_cast<f64>(out);
#endif
#ifdef __arm__
   // TODO
#endif
}