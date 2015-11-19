#ifndef ALEK_HEAP_H
#define ALEK_HEAP_H

#include <types.h>

/**
 * A doubly-linked list that keeps track of heap usage
 */
template<u64 G>
class HeapNode
{
public:
  const static u64 Granularity = G;

public:
  HeapNode(HeapNode *next = nullptr, addr_t start = nullptr, size_t size = 0)
    : next(next)
    , start(start)
    , size(size * G)
    , used(false) { }

public:
  HeapNode *next;
  addr_t start;
  size_t size;
  bool used;
  bool valid;
};

class Heap
{
public:
  Heap() = default;
  virtual ~Heap() = default;

public:
  addr_t malloc(size_t amount);
};

extern "C" addr_t kmalloc(size_t amount);
extern "C" void kfree(addr_t addr);

#endif