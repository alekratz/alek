#ifndef ALEK_SIZES_H
#define ALEK_SIZES_H

#include <types.h>

enum ByteMeasures : u64
{
  b  =      1,
  kb = b  * 1024,
  mb = kb * 1024,
  gb = mb * 1024,
  tb = gb * 1024,
  pb = tb * 1024,
  yb = pb * 1024,
};

template<ByteMeasures suffix=b>
struct ByteMeasure
{
  ByteMeasure(f128 value) : value(value) { }
  ByteMeasure(u64 value) : value(static_cast<f128>(value)) { }
  f128 value;
  operator f128() const
    { return value; }
  template<ByteMeasures s>
  ByteMeasure<s> as()
  {
    return ByteMeasure<s>(value * (suffix / s));
  }
};

ByteMeasure<kb> operator "" _kb(u64 value);
ByteMeasure<mb> operator "" _mb(u64 value);
ByteMeasure<gb> operator "" _gb(u64 value);
ByteMeasure<tb> operator "" _tb(u64 value);
ByteMeasure<pb> operator "" _pb(u64 value);
ByteMeasure<yb> operator "" _yb(u64 value);

ByteMeasure<kb> operator "" _kb(f128 value);
ByteMeasure<mb> operator "" _mb(f128 value);
ByteMeasure<gb> operator "" _gb(f128 value);
ByteMeasure<tb> operator "" _tb(f128 value);
ByteMeasure<pb> operator "" _pb(f128 value);
ByteMeasure<yb> operator "" _yb(f128 value);

#endif