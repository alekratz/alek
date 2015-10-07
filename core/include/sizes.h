#ifndef ALEK_SIZES_H
#define ALEK_SIZES_H

#include <types.h>

enum class ByteSuffixes : u64
{
  b  =      1,
  kb = b  * 1024,
  mb = kb * 1024,
  gb = mb * 1024,
  tb = gb * 1024,
  pb = tb * 1024,
  yb = pb * 1024,
};

template<ByteSuffixes suffix=ByteSuffixes::b>
struct ByteSuffix
{
  ByteSuffix(f128 value) : value(value) { }
  ByteSuffix(u64 value) : value(static_cast<f128>(value)) { }
  f128 value;
  operator f128() const
    { return value * static_cast<f128>(suffix); }
};

ByteSuffix<ByteSuffixes::kb> operator "" _kb(u64 value);
ByteSuffix<ByteSuffixes::mb> operator "" _mb(u64 value);
ByteSuffix<ByteSuffixes::gb> operator "" _gb(u64 value);
ByteSuffix<ByteSuffixes::tb> operator "" _tb(u64 value);
ByteSuffix<ByteSuffixes::pb> operator "" _pb(u64 value);
ByteSuffix<ByteSuffixes::yb> operator "" _yb(u64 value);

ByteSuffix<ByteSuffixes::kb> operator "" _kb(f128 value);
ByteSuffix<ByteSuffixes::mb> operator "" _mb(f128 value);
ByteSuffix<ByteSuffixes::gb> operator "" _gb(f128 value);
ByteSuffix<ByteSuffixes::tb> operator "" _tb(f128 value);
ByteSuffix<ByteSuffixes::pb> operator "" _pb(f128 value);
ByteSuffix<ByteSuffixes::yb> operator "" _yb(f128 value);

#endif