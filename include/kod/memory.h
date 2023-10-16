//
// memory.h
//

#ifndef KOD_MEMORY_H
#define KOD_MEMORY_H

#include <stddef.h>
#include "status.h"

typedef void *(*KodMemoryAllocFn)(size_t, void *);
typedef void *(*KodMemoryReallocFn)(void *, size_t, void *);
typedef void (*KodMemoryDeallocFn)(void *, void *);

typedef struct
{
  KodMemoryAllocFn alloc;
  KodMemoryReallocFn realloc;
  KodMemoryDeallocFn dealloc;
  void *udata;
} KodMemory;

KOD_API void kod_memory_init(KodMemory *mem, KodMemoryAllocFn alloc, KodMemoryReallocFn realloc,
   KodMemoryDeallocFn dealloc, void *udata);
KOD_API void *kod_memory_alloc(KodMemory *mem, size_t size, KodStatus *status);
KOD_API void *kod_memory_realloc(KodMemory *mem, void *ptr, size_t size, KodStatus *status);
KOD_API void kod_memory_dealloc(KodMemory *mem, void *ptr);

#endif // KOD_MEMORY_H
