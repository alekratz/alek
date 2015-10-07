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

// TODO : move these to stdint.h
typedef unsigned char       uint8_t ;
typedef signed char         int8_t  ;

typedef unsigned short      uint16_t;
typedef signed short        int16_t ;

typedef unsigned int        uint32_t;
typedef signed int          int32_t ;

typedef unsigned long long  uint64_t;
typedef signed long long    int64_t ;

typedef int64_t             intmax_t;
typedef uint64_t            uintmax_t;

typedef float               f32;
typedef double              f64;

typedef uint8_t       u8;
typedef int8_t        s8;

typedef uint16_t      u16;
typedef int16_t       s16;

typedef uint32_t      u32;
typedef int32_t       s32;

typedef uint64_t      u64;
typedef int64_t       s64;

static_assert(sizeof(f32) == 4, "F32 is not 32 bits");
static_assert(sizeof(f64) == 8, "F64 is not 64 bits");

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
typedef u64 size_t;

// coordinate type
typedef u32 coord_t;

typedef void* addr_t;
#define AS_ADDR(a) (reinterpret_cast<addr_t>(a))

#endif /* ALEK_TYPES_H */