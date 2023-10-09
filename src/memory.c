//
// memory.c
//

#include "kod/memory.h"

#define check_ptr(p, s) \
  do { \
    if (!(p)) \
    { \
      kod_status_error((s), "out of memory"); \
      return NULL; \
    } \
  } while (0)

void kod_memory_init(KodMemory *mem, KodMemoryAllocFn alloc, KodMemoryReallocFn realloc,
  KodMemoryFreeFn free, void *udata)
{
  mem->alloc = alloc;
  mem->realloc = realloc;
  mem->free = free;
  mem->udata = udata;
}

void *kod_memory_alloc(KodMemory *mem, size_t size, KodStatus *status)
{
  void *ptr = mem->alloc(size, mem->udata);
  check_ptr(ptr, status);
  return ptr;
}

void *kod_memory_realloc(KodMemory *mem, void *ptr, size_t size, KodStatus *status)
{
  void *newPtr = mem->realloc(ptr, size, mem->udata);
  check_ptr(newPtr, status);
  return newPtr;
}

void kod_memory_free(KodMemory *mem, void *ptr)
{
  mem->free(ptr, mem->udata);
}
