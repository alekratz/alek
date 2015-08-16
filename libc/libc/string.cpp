#include "string.h"

size_t strlen(const char* c)
{
  auto c1 = c;
  while(*c1++);
  return c1 - c;
}