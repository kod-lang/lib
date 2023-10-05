//
// config.h
//

#ifndef KOD_CONFIG_H
#define KOD_CONFIG_H

#include <stddef.h>
#include "common.h"

typedef struct
{
  void *(*memoryAlloc)(size_t);
  void *(*memoryRealloc)(void *, size_t);
  void (*memoryFree)(void *);
} KodConfig;

KOD_API void kod_config_set(KodConfig config);
KOD_API void *kod_memory_alloc(size_t size);
KOD_API void *kod_memory_realloc(void *ptr, size_t size);
KOD_API void kod_memory_free(void *ptr);

#endif // KOD_CONFIG_H
