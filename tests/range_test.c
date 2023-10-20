//
// range_test.c
//

#include <assert.h>
#include <stdlib.h>
#include "kod/range.h"

static void *memory_alloc(size_t size, void *udata);
static void *memory_realloc(void *ptr, size_t size, void *udata);
static void memory_dealloc(void *ptr, void *udata);

static KodMemory mem = {
  .alloc = memory_alloc,
  .realloc = memory_realloc,
  .dealloc = memory_dealloc,
  .udata = NULL
};

static inline void range_init_test(void);
static inline void range_new_test(void);
static inline void range_release_test(void);
static inline void range_equal_test(void);

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

static void memory_dealloc(void *ptr, void *udata)
{
  (void) udata;
  free(ptr);
}

static inline void range_init_test(void)
{
  KodRange range;
  kod_range_init(&range, 1, 3);
  assert(range.from == (double) 1);
  assert(range.to == (double) 3);
}

static inline void range_new_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodRange *range = kod_range_new(1, 3, &mem, &status);
  assert(status.isOk);
  assert(range->from == (double) 1);
  assert(range->to == (double) 3);
  kod_range_dealloc(range, &mem);
}

static inline void range_release_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodRange *range = kod_range_new(1, 3, &mem, &status);
  assert(status.isOk);
  kod_inc_ref(&range->obj);
  kod_range_release(range, &mem);
}

static inline void range_equal_test(void)
{
  KodRange range1;
  KodRange range2;
  KodRange range3;
  KodStatus status;
  kod_status_ok(&status);
  kod_range_init(&range1, 1, 3);
  kod_range_init(&range2, 1, 3);
  kod_range_init(&range3, 1, 4);
  assert(kod_range_equal(&range1, &range2));
  assert(!kod_range_equal(&range1, &range3));
}

int main(void)
{
  range_init_test();
  range_new_test();
  range_release_test();
  range_equal_test();
  return EXIT_SUCCESS;
}
