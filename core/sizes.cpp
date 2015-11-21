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
