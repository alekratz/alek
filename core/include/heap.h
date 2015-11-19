#ifndef ALEK_HEAP_H
#define ALEK_HEAP_H

#include <types.h>

/**
 * A doubly-linked list that keeps track of heap usage
 */
class HeapNode
{
public:
  HeapNode(HeapNode *next = nullptr, HeapNode *prev = nullptr, addr_t start = nullptr, size_t size = 0)
    : next(next)
    , prev(prev)
    , start(start)
    , size(size)
    , used(false) { }

public:
  HeapNode *next, *prev;
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

addr_t kmalloc(size_t amount);

#endif