#include "math/sqrt.h"

f64 __arch_sqrt64(f64 num)
{
  f64 out = 0.0;
#ifdef __x86_64__
  asm("fldl %[input]   ;"
      "fsqrt           ;"
      "fstl %[output]  ;"
      : [output] "=r" (out)
      : [input] "r"   (num)
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