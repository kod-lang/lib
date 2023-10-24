//
// function_test.c
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "kod/function.h"

static void *memory_alloc(size_t size, void *udata);
static void *memory_realloc(void *ptr, size_t size, void *udata);
static void memory_dealloc(void *ptr, void *udata);

static KodMemory mem = {
  .alloc = memory_alloc,
  .realloc = memory_realloc,
  .dealloc = memory_dealloc,
  .udata = NULL
};

static inline void function_init_test(void);
static inline void function_new_test(void);
static inline void function_release_test(void);
static inline void function_inplace_add_nonlocal_test(void);
static inline void function_inplace_add_child_test(void);

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

static inline void function_init_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *name = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  KodString *file = kod_string_new_from("bar", &mem, &status);
  assert(status.isOk);
  KodFunction fn;
  kod_function_init(&fn, 1, name, file, &mem, &status);
  assert(status.isOk);
  assert(fn.arity == 1);
  assert(fn.name);
  assert(!strcmp(fn.name->chars, "foo"));
  assert(fn.file);
  assert(!strcmp(fn.file->chars, "bar"));
  assert(!fn.chunk.instructions.count);
  assert(fn.chunk.instructions.elements);
  assert(!fn.chunk.numbers.count);
  assert(fn.chunk.numbers.elements);
  assert(!fn.chunk.strings.count);
  assert(fn.chunk.strings.elements);
  assert(!fn.nonlocals.count);
  assert(fn.nonlocals.elements);
  assert(!fn.functions.count);
  assert(fn.functions.elements);
  kod_function_deinit(&fn, &mem);
}

static inline void function_new_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *name = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  KodString *file = kod_string_new_from("bar", &mem, &status);
  assert(status.isOk);
  KodFunction *fn = kod_function_new(1, name, file, &mem, &status);
  assert(status.isOk);
  assert(fn);
  assert(fn->arity == 1);
  assert(fn->name);
  assert(!strcmp(fn->name->chars, "foo"));
  assert(fn->file);
  assert(!strcmp(fn->file->chars, "bar"));
  assert(!fn->chunk.instructions.count);
  assert(fn->chunk.instructions.elements);
  assert(!fn->chunk.numbers.count);
  assert(fn->chunk.numbers.elements);
  assert(!fn->chunk.strings.count);
  assert(fn->chunk.strings.elements);
  assert(!fn->nonlocals.count);
  assert(fn->nonlocals.elements);
  assert(!fn->functions.count);
  assert(fn->functions.elements);
  kod_function_dealloc(fn, &mem);
}

static inline void function_release_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *name = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  KodString *file = kod_string_new_from("bar", &mem, &status);
  assert(status.isOk);
  KodFunction *fn = kod_function_new(1, name, file, &mem, &status);
  assert(status.isOk);
  kod_inc_ref(&fn->obj);
  kod_function_release(fn, &mem);
}

static inline void function_inplace_add_nonlocal_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *name = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  KodString *file = kod_string_new_from("bar", &mem, &status);
  assert(status.isOk);
  KodFunction fn;
  kod_function_init(&fn, 0, name, file, &mem, &status);
  assert(status.isOk);
  kod_function_inplace_add_nonlocal(&fn, true, 1, &mem, &status);
  assert(status.isOk);
  assert(fn.nonlocals.count == 1);
  assert(fn.nonlocals.elements[0].isLocal);
  assert(fn.nonlocals.elements[0].index == 1);
  kod_function_deinit(&fn, &mem);
}

static inline void function_inplace_add_child_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *name = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  KodString *file = kod_string_new_from("bar", &mem, &status);
  assert(status.isOk);
  KodFunction fn;
  kod_function_init(&fn, 0, name, file, &mem, &status);
  assert(status.isOk);
  KodFunction *child = kod_function_new(0, name, file, &mem, &status);
  assert(status.isOk);
  kod_function_inplace_add_child(&fn, child, &mem, &status);
  assert(status.isOk);
  assert(fn.functions.count == 1);
  assert(fn.functions.elements[0] == child);
  kod_function_deinit(&fn, &mem);
}

int main(void)
{
  function_init_test();
  function_new_test();
  function_release_test();
  function_inplace_add_nonlocal_test();
  function_inplace_add_child_test();
  return EXIT_SUCCESS;
}
