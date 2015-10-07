#ifndef ALEK_SIZES_H
#define ALEK_SIZES_H

#include <types.h>

enum class ByteSuffixes
{
  b,
  kb,
  mb,
  gb,
  tb,
  pb,
  yb,
};

template<ByteSuffixes Suffix=ByteSuffixes::b>
struct ByteSuffix
{
  ByteSuffix(size_t value) : value(value) { }
  size_t value;
  operator size_t() const { return value; }
};

ByteSuffix<ByteSuffixes::kb> operator "" _kb(size_t value);
ByteSuffix<ByteSuffixes::mb> operator "" _mb(size_t value);
ByteSuffix<ByteSuffixes::gb> operator "" _gb(size_t value);
ByteSuffix<ByteSuffixes::tb> operator "" _tb(size_t value);
ByteSuffix<ByteSuffixes::pb> operator "" _pb(size_t value);
ByteSuffix<ByteSuffixes::yb> operator "" _yb(size_t value);

#endif