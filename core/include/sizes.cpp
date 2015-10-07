#include "sizes.h"

ByteSuffix<ByteSuffixes::kb> operator "" _kb(size_t value)
{ return ByteSuffix<ByteSuffixes::kb>(value); }

ByteSuffix<ByteSuffixes::mb> operator "" _mb(size_t value)
{ return ByteSuffix<ByteSuffixes::mb>(value); }

ByteSuffix<ByteSuffixes::gb> operator "" _gb(size_t value)
{ return ByteSuffix<ByteSuffixes::gb>(value); }

ByteSuffix<ByteSuffixes::tb> operator "" _tb(size_t value)
{ return ByteSuffix<ByteSuffixes::tb>(value); }

ByteSuffix<ByteSuffixes::pb> operator "" _pb(size_t value)
{ return ByteSuffix<ByteSuffixes::pb>(value); }

ByteSuffix<ByteSuffixes::yb> operator "" _yb(size_t value)
{ return ByteSuffix<ByteSuffixes::yb>(value); }
