#include "heap.h"
#include "kernel.h"
#include "sizes.h"

#include <mem.h>

typedef HeapNode<128> KHeapNode;

extern addr_t kern_heap_start;
extern size_t kern_heap_size;
extern KHeapNode kern_heap_info_start;
extern KHeapNode kern_heap_info_end;

static KHeapNode *heap_info_start_ptr = &kern_heap_info_start;
static KHeapNode *heap_info_end_ptr = &kern_heap_info_end;
static addr_t heap_start = &kern_heap_start;

static bool kmalloc_init();
static KHeapNode *alloc_kern_heapnode();

/**
 * Initializes the kernel heap
 * @return whether initialization was successful. Kernel should panic if not.
 */
static bool kmalloc_init()
{
  static bool kmalloc_ready = false;
  if(kmalloc_ready)
    panic("kmalloc_init: kmalloc_init called twice");

  // memset the entire kernel heap to zero
  memset(heap_info_start_ptr, 0, sizeof(heap_info_start_ptr) * kern_heap_size);

  heap_info_start_ptr[0].start = heap_start;
  heap_info_start_ptr[0].size = kern_heap_size / KHeapNode::Granularity;
  heap_info_start_ptr[0].valid = true;

  return kmalloc_ready = true;
}

/**
 * Finds the first instance of an invalid heap pointer.
 * @return the address of a heap node that does not have the valid bit set.
 */
static KHeapNode *alloc_kern_heapnode()
{
  auto heap_ptr = heap_info_start_ptr;
  for(; heap_ptr < heap_info_end_ptr; heap_ptr++)
  {
    if(!heap_ptr->valid)
    {
      heap_ptr->valid = true;
      return heap_ptr;
    }
  }
  return nullptr;
}

/**
 * Allocates items on the kernel's heap.
 * @param  amount the amount of memory to allocate.
 * @return        a pointer to the memory allocated, or nullptr if no memory was allocated.
 */
extern "C" addr_t kmalloc(size_t amount)
{
  static bool kmalloc_ready = false;
  if(!kmalloc_ready && (kmalloc_ready = true, !kmalloc_init()))
    panic("kmalloc: could not initialize kmalloc");

  size_t blocks = (amount / KHeapNode::Granularity) + 1;
  // Find the first fit
  auto heap_ptr = heap_info_start_ptr;
  for(; heap_ptr && !(heap_ptr->size >= blocks && !heap_ptr->used); heap_ptr = heap_ptr->next);

  // There were no spaces large enough to allocate our heap
  if(heap_ptr == nullptr)
    panic("kmalloc: no memory available to allocate");

  if(blocks < heap_ptr->size)
  {
    auto old_next = heap_ptr->next;
    auto new_next = alloc_kern_heapnode();
    if(new_next == nullptr)
      panic("kmalloc: could not allocate heap node");

    heap_ptr->next = new_next;
    new_next->next = old_next;
    new_next->used = false;
    new_next->size = heap_ptr->size - blocks;
    new_next->start = AS_ADDR(AS_U32(heap_ptr->start) + 
      (blocks * KHeapNode::Granularity));
  }

  heap_ptr->size = blocks;
  heap_ptr->used = true;

  return heap_ptr->start;
}

extern "C" void kfree(addr_t addr)
{
  // find which block this address belongs to
  auto heap_ptr = heap_info_start_ptr;
  for(; heap_ptr && heap_ptr->start != addr; heap_ptr = heap_ptr->next);

  // something went wrong here, but we are forgiving. kind of.
  if(heap_ptr == nullptr)
    panic("kfree: tried to free a non-allocated pointer");

  heap_ptr->used = false;
  // absorb forward
}