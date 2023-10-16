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
static inline void stack_inplace_push_value_test(void);
static inline void stack_inplace_push_object_test(void);
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
  KodStack stack;
  kod_stack_init(&stack, KOD_STACK_DEFAULT_SIZE, &mem, &status);
  assert(status.isOk);
  assert(stack.size == KOD_STACK_DEFAULT_SIZE);
  assert(stack.slots);
  assert(stack.top == &stack.slots[-1]);
  assert(stack.end == &stack.slots[KOD_STACK_DEFAULT_SIZE - 1]);
  kod_stack_deinit(&stack, &mem);
}

static inline void stack_inplace_push_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodStack stack;
  kod_stack_init(&stack, KOD_STACK_DEFAULT_SIZE, &mem, &status);
  assert(status.isOk);
  kod_stack_inplace_push(&stack, kod_number_value(1.23), &status);
  assert(status.isOk);
  assert(stack.top == &stack.slots[0]);
  assert(kod_as_number(kod_stack_peek(&stack, 0)) == (double) 1.23);
  KodString *str = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  kod_stack_inplace_push(&stack, kod_string_value(str), &status);
  assert(status.isOk);
  assert(stack.top == &stack.slots[1]);
  assert(kod_as_string(kod_stack_peek(&stack, 0)) == str);
  assert(kod_ref_count(&str->obj) == 1);
  kod_stack_deinit(&stack, &mem);
}

static inline void stack_inplace_push_value_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodStack stack;
  kod_stack_init(&stack, KOD_STACK_DEFAULT_SIZE, &mem, &status);
  assert(status.isOk);
  kod_stack_inplace_push_value(&stack, kod_number_value(1.23), &status);
  assert(status.isOk);
  assert(stack.top == &stack.slots[0]);
  assert(kod_as_number(kod_stack_peek(&stack, 0)) == (double) 1.23);
  kod_stack_deinit(&stack, &mem);
}

static inline void stack_inplace_push_object_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodStack stack;
  kod_stack_init(&stack, KOD_STACK_DEFAULT_SIZE, &mem, &status);
  assert(status.isOk);
  KodString *str = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  kod_stack_inplace_push_object(&stack, kod_string_value(str), &status);
  assert(status.isOk);
  assert(stack.top == &stack.slots[0]);
  assert(kod_as_string(kod_stack_peek(&stack, 0)) == str);
  assert(kod_ref_count(&str->obj) == 1);
  kod_stack_deinit(&stack, &mem);
}

static inline void stack_inplace_pop_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodStack stack;
  kod_stack_init(&stack, KOD_STACK_DEFAULT_SIZE, &mem, &status);
  assert(status.isOk);
  KodString *str = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  kod_stack_inplace_push_object(&stack, kod_string_value(str), &status);
  assert(status.isOk);
  kod_stack_inplace_pop(&stack, &mem);
  assert(stack.top == &stack.slots[-1]);
  kod_stack_deinit(&stack, &mem);
}

int main(void)
{
  stack_init_test();
  stack_inplace_push_test();
  stack_inplace_push_value_test();
  stack_inplace_push_object_test();
  stack_inplace_pop_test();
  return EXIT_SUCCESS;
}
