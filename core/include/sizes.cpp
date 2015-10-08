#include "sizes.h"

ByteMeasure<kb> operator "" _kb(u64 value)
{ return ByteMeasure<kb>(value); }
ByteMeasure<mb> operator "" _mb(u64 value)
{ return ByteMeasure<mb>(value); }
ByteMeasure<gb> operator "" _gb(u64 value)
{ return ByteMeasure<gb>(value); }
ByteMeasure<tb> operator "" _tb(u64 value)
{ return ByteMeasure<tb>(value); }
ByteMeasure<pb> operator "" _pb(u64 value)
{ return ByteMeasure<pb>(value); }
ByteMeasure<yb> operator "" _yb(u64 value)
{ return ByteMeasure<yb>(value); }

ByteMeasure<kb> operator "" _kb(f128 value)
{ return ByteMeasure<kb>(value); }
ByteMeasure<mb> operator "" _mb(f128 value)
{ return ByteMeasure<mb>(value); }
ByteMeasure<gb> operator "" _gb(f128 value)
{ return ByteMeasure<gb>(value); }
ByteMeasure<tb> operator "" _tb(f128 value)
{ return ByteMeasure<tb>(value); }
ByteMeasure<pb> operator "" _pb(f128 value)
{ return ByteMeasure<pb>(value); }
ByteMeasure<yb> operator "" _yb(f128 value)
{ return ByteMeasure<yb>(value); }
