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

#ifndef ALEK_LIBM_INTERNAL_COMMON_H
#define ALEK_LIBM_INTERNAL_COMMON_H

#include <machine/ieeefp.h>

/**
 * All of the following were stolen from newlib's libm math library
 */

#ifndef __IEEE_BIG_ENDIAN
#ifndef __IEEE_LITTLE_ENDIAN
  #error Must define endianness
#endif
#endif

/* A union which permits us to convert between a double and two 32 bit
   ints.  */
#ifdef __IEEE_BIG_ENDIAN
typedef union 
{
  double value;
  struct 
  {
    u32 msw;
    u32 lsw;
  } parts;
} ieee_double_shape_type;
#endif

#ifdef __IEEE_LITTLE_ENDIAN
typedef union 
{
  double value;
  struct 
  {
    u32 lsw;
    u32 msw;
  } parts;
} ieee_double_shape_type;
#endif

/* Get two 32 bit ints from a double.  */

#define EXTRACT_WORDS(ix0,ix1,d)        \
do {                \
  ieee_double_shape_type ew_u;          \
  ew_u.value = (d);           \
  (ix0) = ew_u.parts.msw;         \
  (ix1) = ew_u.parts.lsw;         \
} while (0)

/* Get the more significant 32 bit int from a double.  */

#define GET_HIGH_WORD(i,d)          \
do {                \
  ieee_double_shape_type gh_u;          \
  gh_u.value = (d);           \
  (i) = gh_u.parts.msw;           \
} while (0)

/* Get the less significant 32 bit int from a double.  */

#define GET_LOW_WORD(i,d)         \
do {                \
  ieee_double_shape_type gl_u;          \
  gl_u.value = (d);           \
  (i) = gl_u.parts.lsw;           \
} while (0)

/* Set a double from two 32 bit ints.  */

#define INSERT_WORDS(d,ix0,ix1)         \
do {                \
  ieee_double_shape_type iw_u;          \
  iw_u.parts.msw = (ix0);         \
  iw_u.parts.lsw = (ix1);         \
  (d) = iw_u.value;           \
} while (0)

/* Set the more significant 32 bits of a double from an int.  */

#define SET_HIGH_WORD(d,v)          \
do {                \
  ieee_double_shape_type sh_u;          \
  sh_u.value = (d);           \
  sh_u.parts.msw = (v);           \
  (d) = sh_u.value;           \
} while (0)

/* Set the less significant 32 bits of a double from an int.  */

#define SET_LOW_WORD(d,v)         \
do {                \
  ieee_double_shape_type sl_u;          \
  sl_u.value = (d);           \
  sl_u.parts.lsw = (v);           \
  (d) = sl_u.value;           \
} while (0)

/* A union which permits us to convert between a float and a 32 bit
   int.  */

typedef union
{
  float value;
  u32 word;
} ieee_float_shape_type;

/* Get a 32 bit int from a float.  */

#define GET_FLOAT_WORD(i,d)         \
do {                \
  ieee_float_shape_type gf_u;         \
  gf_u.value = (d);           \
  (i) = gf_u.word;            \
} while (0)

/* Set a float from a 32 bit int.  */

#define SET_FLOAT_WORD(d,i)         \
do {                \
  ieee_float_shape_type sf_u;         \
  sf_u.word = (i);            \
  (d) = sf_u.value;           \
} while (0)

/* Macros to avoid undefined behaviour that can arise if the amount
   of a shift is exactly equal to the size of the shifted operand.  */

#define SAFE_LEFT_SHIFT(op,amt)         \
  (((amt) < 8 * sizeof(op)) ? ((op) << (amt)) : 0)

#define SAFE_RIGHT_SHIFT(op,amt)        \
  (((amt) < 8 * sizeof(op)) ? ((op) >> (amt)) : 0)

#endif /* ALEK_LIBM_INTERNAL_COMMON_H */