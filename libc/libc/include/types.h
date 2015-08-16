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

#ifndef ALEK_TYPES_H
#define ALEK_TYPES_H

typedef float               f32;
typedef double              f64;

typedef unsigned char       u8 ;
typedef signed char         s8 ;

typedef unsigned short      u16;
typedef signed short        s16;

typedef unsigned int        u32;
typedef signed int          s32;

typedef unsigned long long  u64;
typedef signed long long    s64;

static_assert(sizeof(u8) == 1, "U8 is not 8 bits");
static_assert(sizeof(s8) == 1, "S8 is not 8 bits");
static_assert(sizeof(u16) == 2, "U16 is not 16 bits");
static_assert(sizeof(s16) == 2, "S16 is not 16 bits");
static_assert(sizeof(u32) == 4, "U32 is not 32 bits");
static_assert(sizeof(s32) == 4, "S32 is not 32 bits");
static_assert(sizeof(u64) == 8, "U64 is not 64 bits");
static_assert(sizeof(s64) == 8, "S64 is not 64 bits");

// results are strictly a signed 32-bit integer
typedef s32 result_t;
#define R_OK 0
#define R_FAIL (-1)

// size_t
typedef u32 size_t;

// coordinate type
typedef u32 coord_t;

typedef void* addr_t;
#define AS_ADDR(a) (reinterpret_cast<addr_t>(a))

#endif /* ALEK_TYPES_H */