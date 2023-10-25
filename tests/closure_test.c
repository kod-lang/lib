//
// closure_test.c
//

#include <assert.h>
#include <stdlib.h>
#include "kod/closure.h"

static void *memory_alloc(size_t size, void *udata);
static void *memory_realloc(void *ptr, size_t size, void *udata);
static void memory_dealloc(void *ptr, void *udata);

static KodMemory mem = {
  .alloc = memory_alloc,
  .realloc = memory_realloc,
  .dealloc = memory_dealloc,
  .udata = NULL
};

static inline void closure_init_test(void);
static inline void closure_new_test(void);
static inline void closure_release_test(void);

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

static inline void closure_init_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *name = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  KodString *file = kod_string_new_from("bar", &mem, &status);
  assert(status.isOk);
  KodFunction *fn = kod_function_new(1, name, file, &mem, &status);
  assert(status.isOk);
  KodClosure cl;
  kod_closure_init(&cl, fn, &mem, &status);
  assert(status.isOk);
  assert(!kod_ref_count(&cl.obj));
  assert(cl.fn);
  assert(cl.nonlocals);
  kod_closure_deinit(&cl, &mem);
}

static inline void closure_new_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *name = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  KodString *file = kod_string_new_from("bar", &mem, &status);
  assert(status.isOk);
  KodFunction *fn = kod_function_new(1, name, file, &mem, &status);
  assert(status.isOk);
  KodClosure *cl = kod_closure_new(fn, &mem, &status);
  assert(status.isOk);
  assert(cl);
  assert(!kod_ref_count(&cl->obj));
  assert(cl->fn);
  assert(cl->nonlocals);
  kod_closure_dealloc(cl, &mem);
}

static inline void closure_release_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *name = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  KodString *file = kod_string_new_from("bar", &mem, &status);
  assert(status.isOk);
  KodFunction *fn = kod_function_new(1, name, file, &mem, &status);
  assert(status.isOk);
  KodClosure *cl = kod_closure_new(fn, &mem, &status);
  assert(status.isOk);
  kod_inc_ref(&cl->obj);
  kod_closure_release(cl, &mem);
}

int main(void)
{
  closure_init_test();
  closure_new_test();
  closure_release_test();
  return EXIT_SUCCESS;
}
