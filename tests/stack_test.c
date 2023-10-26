//
// stack_test.c
//

#include <assert.h>
#include <stdlib.h>
#include "kod/stack.h"
#include "kod/string.h"

static void *memory_alloc(size_t size, void *udata);
static void *memory_realloc(void *ptr, size_t size, void *udata);
static void memory_dealloc(void *ptr, void *udata);

static KodMemory mem = {
  .alloc = memory_alloc,
  .realloc = memory_realloc,
  .dealloc = memory_dealloc,
  .udata = NULL
};

static inline void stack_init_test(void);
static inline void stack_inplace_push_test(void);
static inline void stack_inplace_pop_test(void);

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

static inline void stack_init_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodStack(int) stack = { 0 };
  kod_stack_init(&stack, KOD_STACK_DEFAULT_SIZE, &mem, &status);
  assert(status.isOk);
  assert(stack.size == KOD_STACK_DEFAULT_SIZE);
  assert(stack.elements);
  assert(stack.top == &stack.elements[-1]);
  assert(stack.end == &stack.elements[KOD_STACK_DEFAULT_SIZE - 1]);
  kod_stack_deinit(&stack, &mem);
}

static inline void stack_inplace_push_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodStack(int) stack = { 0 };
  kod_stack_init(&stack, KOD_STACK_DEFAULT_SIZE, &mem, &status);
  assert(status.isOk);
  kod_stack_inplace_push(&stack, 1, &status);
  assert(status.isOk);
  assert(stack.top == &stack.elements[0]);
  assert(kod_stack_peek(&stack, 0) == 1);
  kod_stack_deinit(&stack, &mem);
}

static inline void stack_inplace_pop_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodStack(int) stack = { 0 };
  kod_stack_init(&stack, KOD_STACK_DEFAULT_SIZE, &mem, &status);
  assert(status.isOk);
  kod_stack_inplace_push(&stack, 1, &status);
  assert(status.isOk);
  kod_stack_inplace_pop(&stack, &mem);
  assert(stack.top == &stack.elements[-1]);
  kod_stack_deinit(&stack, &mem);
}

int main(void)
{
  stack_init_test();
  stack_inplace_push_test();
  stack_inplace_pop_test();
  return EXIT_SUCCESS;
}
