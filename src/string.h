#ifndef AAA_STRING_H
#define AAA_STRING_H
#include "types.h"

inline size_t strlen(const char *buf)
{
  const char *end = buf;
  while(*end++);
  return end - buf;
}

#endif