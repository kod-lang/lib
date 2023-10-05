//
// config.c
//

#include "kod/config.h"

static KodConfig _config = { 0 };

void kod_config_set(KodConfig config)
{
  _config = config;
}

void *kod_memory_alloc(size_t size)
{
  return _config.memoryAlloc(size);
}

void *kod_memory_realloc(void *ptr, size_t size)
{
  return _config.memoryRealloc(ptr, size);
}

void kod_memory_free(void *ptr)
{
  _config.memoryFree(ptr);
}
