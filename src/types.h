#ifndef AAA_TYPES_H
#define AAA_TYPES_H

typedef unsigned char       u8;
typedef signed char         s8;

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

typedef void* addr_t;

#endif /* AAA_TYPES_H */