#include "string.h"

size_t strlen(const char* c)
{
  if(!*c)
    return 0;
  auto c1 = c;
  while(*++c1);
  return c1 - c;
}