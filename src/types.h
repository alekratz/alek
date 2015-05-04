#ifndef TYPES_H
#define TYPES_H

typedef unsigned char   u8;
typedef signed char     s8;

typedef unsigned short  u16;
typedef signed short    s16;

typedef unsigned int    u32;
typedef signed int      s32;

typedef unsigned long   u64;
typedef signed int      s64;

// results are strictly a signed 32-bit integer
typedef s32 result_t;
#define R_OK 0
#define R_FAIL (-1)

#endif