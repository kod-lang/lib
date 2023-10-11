//
// memory_test.c
//

#include <assert.h>
#include <stdlib.h>
#include "kod/memory.h"

static inline void memory_init_test(void);
static inline void memory_alloc_test(void);
static inline void memory_realloc_test(void);
static void *memory_alloc(size_t size, void *udata);
static void *memory_realloc(void *ptr, size_t size, void *udata);
static void memory_free(void *ptr, void *udata);

static void *memory_alloc(size_t size, void *udata)
{
  (void) udata;
  return malloc(size);
}

static void *memory_realloc(void *ptr, size_t size, void *udata)
{
  (void) udata;
  return realloc(ptr, size);
}

static void memory_free(void *ptr, void *udata)
{
  (void) udata;
  free(ptr);
}

static inline void memory_init_test(void)
{
  KodMemory mem;
  kod_memory_init(&mem, memory_alloc, memory_realloc, memory_free, NULL);
  assert(mem.alloc);
  assert(mem.realloc);
  assert(mem.free);
  assert(!mem.udata);
}

static inline void memory_alloc_test(void)
{
  KodMemory mem;
  kod_memory_init(&mem, memory_alloc, memory_realloc, memory_free, NULL);
  KodStatus status;
  kod_status_ok(&status);
  int *ptr = kod_memory_alloc(&mem, sizeof(*ptr), &status);
  assert(status.isOk);
  assert(ptr);
  *ptr = 1;
  assert(*ptr == 1);
  kod_memory_free(&mem, ptr);
}

static inline void memory_realloc_test(void)
{
  KodMemory mem;
  kod_memory_init(&mem, memory_alloc, memory_realloc, memory_free, NULL);
  KodStatus status;
  kod_status_ok(&status);
  int *ptr1 = kod_memory_alloc(&mem, sizeof(*ptr1), &status);
  *ptr1 = 1;
  int *ptr2 = kod_memory_realloc(&mem, ptr1, sizeof(*ptr2) * 2, &status);
  assert(status.isOk);
  assert(ptr2);
  ptr2[1] = 2;
  assert(ptr2[0] == 1);
  assert(ptr2[1] == 2);
  kod_memory_free(&mem, ptr2);
}

int main(void)
{
  memory_init_test();
  memory_alloc_test();
  memory_realloc_test();
  return EXIT_SUCCESS;
}
