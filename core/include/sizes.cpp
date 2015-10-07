#include "sizes.h"

ByteSuffix<ByteSuffixes::kb> operator "" _kb(u64 value)
{ return ByteSuffix<ByteSuffixes::kb>(value); }
ByteSuffix<ByteSuffixes::mb> operator "" _mb(u64 value)
{ return ByteSuffix<ByteSuffixes::mb>(value); }
ByteSuffix<ByteSuffixes::gb> operator "" _gb(u64 value)
{ return ByteSuffix<ByteSuffixes::gb>(value); }
ByteSuffix<ByteSuffixes::tb> operator "" _tb(u64 value)
{ return ByteSuffix<ByteSuffixes::tb>(value); }
ByteSuffix<ByteSuffixes::pb> operator "" _pb(u64 value)
{ return ByteSuffix<ByteSuffixes::pb>(value); }
ByteSuffix<ByteSuffixes::yb> operator "" _yb(u64 value)
{ return ByteSuffix<ByteSuffixes::yb>(value); }

ByteSuffix<ByteSuffixes::kb> operator "" _kb(f128 value)
{ return ByteSuffix<ByteSuffixes::kb>(value); }
ByteSuffix<ByteSuffixes::mb> operator "" _mb(f128 value)
{ return ByteSuffix<ByteSuffixes::mb>(value); }
ByteSuffix<ByteSuffixes::gb> operator "" _gb(f128 value)
{ return ByteSuffix<ByteSuffixes::gb>(value); }
ByteSuffix<ByteSuffixes::tb> operator "" _tb(f128 value)
{ return ByteSuffix<ByteSuffixes::tb>(value); }
ByteSuffix<ByteSuffixes::pb> operator "" _pb(f128 value)
{ return ByteSuffix<ByteSuffixes::pb>(value); }
ByteSuffix<ByteSuffixes::yb> operator "" _yb(f128 value)
{ return ByteSuffix<ByteSuffixes::yb>(value); }
