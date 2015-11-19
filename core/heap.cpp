#include "heap.h"
#include "kernel.h"

#include <mem.h>

extern addr_t kern_heap_start;
extern size_t kern_heap_size;
extern HeapNode kern_heap_info_start;
extern HeapNode kern_heap_info_end;

static HeapNode *heap_info_start_ptr = &kern_heap_info_start;
static HeapNode *heap_info_end_ptr = &kern_heap_info_end;
static addr_t heap_start = &kern_heap_start;

static bool kmalloc_init();
static HeapNode *alloc_kern_heapnode();

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
  heap_info_start_ptr[0].size = kern_heap_size;
  heap_info_start_ptr[0].valid = true;

  return kmalloc_ready = true;
}

/**
 * Finds the first instance of an invalid heap pointer.
 * @return the address of a heap node that does not have the valid bit set.
 */
static HeapNode *alloc_kern_heapnode()
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
addr_t kmalloc(size_t amount)
{
  static bool kmalloc_ready = false;
  if(!kmalloc_ready && (kmalloc_ready = true, !kmalloc_init()))
    panic("kmalloc: could not initialize kmalloc");

  // Find the first fit
  auto heap_ptr = heap_info_start_ptr;
  for(; heap_ptr && !(heap_ptr->size >= amount && !heap_ptr->used); heap_ptr = heap_ptr->next);

  // There were no spaces large enough to allocate our heap
  if(heap_ptr == nullptr)
    panic("kmalloc: no memory available to allocate");

  if(amount < heap_ptr->size)
  {
    auto old_next = heap_ptr->next;
    auto new_next = alloc_kern_heapnode();
    if(new_next == nullptr)
      panic("kmalloc: could not allocate heap node");

    heap_ptr->next = new_next;
    new_next->prev = heap_ptr;
    new_next->next = old_next;
    new_next->used = false;
    new_next->size = heap_ptr->size - amount;
    new_next->start = heap_ptr->start + amount;
  }

  heap_ptr->size = amount;
  heap_ptr->used = true;

  return heap_ptr->start;
}