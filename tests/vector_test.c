//
// vector_test.c
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "kod/vector.h"

static void *memory_alloc(size_t size, void *udata);
static void *memory_realloc(void *ptr, size_t size, void *udata);
static void memory_dealloc(void *ptr, void *udata);

static KodMemory mem = {
  .alloc = memory_alloc,
  .realloc = memory_realloc,
  .dealloc = memory_dealloc,
  .udata = NULL
};

static inline void vector_init_with_capacity_test(void);
static inline void vector_init_with_capacity_less_than_min_test(void);
static inline void vector_init_with_capacity_greater_than_max_test(void);
static inline void vector_init_test(void);
static inline void vector_inplace_add_test(void);
static inline void vector_inplace_set_test(void);
static inline void vector_inplace_remove_at_test(void);
static inline void vector_inplace_clear_test(void);

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

static inline void vector_init_with_capacity_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodVector(int) vec = { 0 };
  kod_vector_init_with_capacity(&vec, 8, &mem, &status);
  assert(status.isOk);
  assert(vec.capacity == 8);
  kod_vector_deinit(&vec, &mem);
}

static inline void vector_init_with_capacity_less_than_min_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodVector(int) vec = { 0 };
  kod_vector_init_with_capacity(&vec, KOD_VECTOR_MIN_CAPACITY - 1, &mem, &status);
  assert(status.isOk);
  assert(vec.capacity == KOD_VECTOR_MIN_CAPACITY);
  kod_vector_deinit(&vec, &mem);
}

static inline void vector_init_with_capacity_greater_than_max_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodVector(int) vec = { 0 };
  kod_vector_init_with_capacity(&vec, KOD_VECTOR_MAX_CAPACITY + 1, &mem, &status);
  assert(!status.isOk);
  assert(!strcmp(status.error, "vector capacity exceeds maximum"));
}

static inline void vector_init_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodVector(int) vec = { 0 };
  kod_vector_init(&vec, &mem, &status);
  assert(status.isOk);
  assert(vec.capacity == KOD_VECTOR_MIN_CAPACITY);
  assert(!vec.count);
  assert(vec.elements);
  kod_vector_deinit(&vec, &mem);
}

static inline void vector_inplace_add_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodVector(int) vec = { 0 };
  kod_vector_init(&vec, &mem, &status);
  assert(status.isOk);
  kod_vector_inplace_add(&vec, 1, &mem, &status);
  assert(status.isOk);
  assert(vec.count == 1);
  assert(vec.elements[0] == 1);
  kod_vector_deinit(&vec, &mem);
}

static inline void vector_inplace_set_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodVector(int) vec = { 0 };
  kod_vector_init(&vec, &mem, &status);
  assert(status.isOk);
  kod_vector_inplace_add(&vec, 1, &mem, &status);
  assert(status.isOk);
  kod_vector_inplace_set(&vec, 0, 2);
  assert(status.isOk);
  assert(vec.count == 1);
  assert(vec.elements[0] == 2);
  kod_vector_deinit(&vec, &mem);
}

static inline void vector_inplace_remove_at_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodVector(int) vec = { 0 };
  kod_vector_init(&vec, &mem, &status);
  assert(status.isOk);
  kod_vector_inplace_add(&vec, 1, &mem, &status);
  assert(status.isOk);
  kod_vector_inplace_add(&vec, 2, &mem, &status);
  assert(status.isOk);
  kod_vector_inplace_add(&vec, 3, &mem, &status);
  assert(status.isOk);
  kod_vector_inplace_remove_at(&vec, 1);
  assert(status.isOk);
  assert(vec.count == 2);
  assert(vec.elements[0] == 1);
  assert(vec.elements[1] == 3);
  kod_vector_deinit(&vec, &mem);
}

static inline void vector_inplace_clear_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodVector(int) vec = { 0 };
  kod_vector_init(&vec, &mem, &status);
  assert(status.isOk);
  kod_vector_inplace_add(&vec, 1, &mem, &status);
  assert(status.isOk);
  kod_vector_inplace_clear(&vec);
  assert(!vec.count);
  kod_vector_deinit(&vec, &mem);
}

int main(void)
{
  vector_init_with_capacity_test();
  vector_init_with_capacity_less_than_min_test();
  vector_init_with_capacity_greater_than_max_test();
  vector_init_test();
  vector_inplace_add_test();
  vector_inplace_set_test();
  vector_inplace_remove_at_test();
  vector_inplace_clear_test();
  return EXIT_SUCCESS;
}
