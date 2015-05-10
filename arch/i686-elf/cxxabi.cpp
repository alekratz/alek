#include "abi/cxxabi.h"

// wow I am lazy
// Macro for checking if an entry is empty
#define IS_ENTRY_EMPTY(entry) (entry.dtor_fun == nullptr && entry.obj_ptr == nullptr && entry.dso_handle == nullptr)
#define MAX_ATEXIT_FUN 128 // the maximum amount of fun in this file is 128. no more is allowed

extern "C" {
typedef struct atexit_fun_entry
{
  // Each member is 4 bytes, 3 * 4 * 128 = 3 * 2^2 * 2^7 = 3 * 2^9 = 1.5Kb
  void (*dtor_fun)(addr_t);
  addr_t obj_ptr;
  addr_t dso_handle;
} atexit_fun_entry_t;

// Table of atexit functions
atexit_fun_entry_t __atexit_funs[MAX_ATEXIT_FUN];
// Number of filled entries
u32 __atexit_fun_count = 0;

// Dynamic Shared Object handle
// Optimally, we should remove = nullptr (i.e. remove it from the .data section)
// and initialize it somewhere in the assembly
addr_t __dso_handle = nullptr;

/**
 * Helper function that fills in any holes in the atexit functions
 */
static void fill_empty_atexit_funs();
/**
 * Helper function that shifts the atexit functions left N spaces
 */
static void shl_atexit_funs(u32 start, u32 n);

s32 __cxa_atexit(void (*dtor) (addr_t), addr_t arg, addr_t dso)
{
  if(__atexit_fun_count >= MAX_ATEXIT_FUN) 
    // too much fun is being had
    return R_FAIL;

  __atexit_funs[__atexit_fun_count].dtor_fun = dtor;
  __atexit_funs[__atexit_fun_count].obj_ptr = arg;
  __atexit_funs[__atexit_fun_count].dso_handle = dso;
  __atexit_fun_count++;
  return R_OK;
}

void __cxa_finalize(addr_t dso)
{
  s32 i = __atexit_fun_count;
  atexit_fun_entry_t *funs = __atexit_funs;

  if(dso == nullptr)
  {
    /*
     * According to the Itanium C++ ABI, if __cxa_finalize is called without
     * a function pointer, then DESTROY EVERYTHING
     * (go top-down, because the top is going to have the most recent objects,
     * and it's probably better to free those objects in order)
     */
    while(--i >= 0)
    {
      if(funs[i].dtor_fun)
        // call the destructor (if it's not pure virtual) and pass it the
        // pointer of the object
        funs[i].dtor_fun(funs[i].obj_ptr);
    }
  }
  else
  {
    // ABI states that all objects with the matching DSO handle are removed
    for( ; i >= 0; i--)
    {
      if(funs[i].dso_handle == dso)
      {
        // call the dtor
        funs[i].dtor_fun(funs[i].obj_ptr);
        // null it out; it will help when shifting everything over
        funs[i].dtor_fun = nullptr;
        funs[i].obj_ptr = nullptr;
        funs[i].dso_handle = nullptr;
      }
      // fill in the holes
      fill_empty_atexit_funs();
    }
  }
}

static void fill_empty_atexit_funs()
{
  u32 start, end;
  atexit_fun_entry_t *funs = __atexit_funs;
  for(start = 0; start < MAX_ATEXIT_FUN; start++)
  {
    if(IS_ENTRY_EMPTY(funs[start]))
    {
      // start traversing until we either reach the end or bump into something else
      for(end = start; end < MAX_ATEXIT_FUN && IS_ENTRY_EMPTY(funs[start]); end++);
      // check to see which condition ended the loop
      if(end == MAX_ATEXIT_FUN) return;
      // actually execute the shift
      shl_atexit_funs(start, end - start);
    }
  }
}

static void shl_atexit_funs(u32 start, u32 n)
{
  atexit_fun_entry_t *funs = __atexit_funs;
  for( ; start < MAX_ATEXIT_FUN; start++)
  {
    // shift it over
    funs[start - n] = funs[start];
    // zero out this one - we don't need it anymore
    funs[start].dtor_fun = nullptr;
    funs[start].obj_ptr = nullptr;
    funs[start].dso_handle = nullptr;
  }
}

} /* extern "C" */