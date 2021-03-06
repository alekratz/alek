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
static bool kmalloc_ready = false;

static KHeapNode *alloc_kern_heapnode();
static void absorb_forward(KHeapNode *head);

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
 * Takes all of the de-allocated memory blocks in front of this memory block, and
 * adds their size to ours.
 * @param head the memory block that was just de-allocated
 */
static void absorb_forward(KHeapNode *head)
{
  if(!head->next || head->next->used)
    return;

  for(auto next_ptr = head->next; next_ptr && !next_ptr->used; next_ptr = next_ptr->next)
  {
    next_ptr->valid = false;
    head->size += next_ptr->size;
  }
}

/**
 * Initializes the kernel heap
 * @return whether initialization was successful. Kernel should panic if not.
 */
void init_kheap()
{
  if(kmalloc_ready)
    panic("kmalloc_init: kmalloc_init called twice");

  // memset the entire kernel heap to zero
  memset(heap_info_start_ptr, 0, sizeof(heap_info_start_ptr) * kern_heap_size);

  heap_info_start_ptr[0].start = heap_start;
  heap_info_start_ptr[0].size = kern_heap_size / KHeapNode::Granularity;
  heap_info_start_ptr[0].valid = true;

  kmalloc_ready = true;
}

/**
 * Allocates items on the kernel's heap.
 * @param  amount the amount of memory to allocate.
 * @return        a pointer to the memory allocated, or nullptr if no memory was allocated.
 */
extern "C" addr_t kmalloc(size_t amount)
{
  if(!kmalloc_ready)
    panic("kmalloc: the heap has not been initialized for utilization by kmalloc");
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
  absorb_forward(heap_ptr);
}