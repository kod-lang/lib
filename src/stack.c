//
// stack.c
//

#include "kod/stack.h"

void kod_stack_init(KodStack *stack, int size, KodMemory *mem, KodStatus *status)
{
  KodValue *slots = kod_memory_alloc(mem, sizeof(*slots) * size, status);
  if (!status->isOk)
    return;
  stack->size = size;
  stack->slots = slots;
  stack->top = &slots[-1];
  stack->end = &slots[size - 1];
}

void kod_stack_deinit(KodStack *stack, KodMemory *mem)
{
  KodValue *slots = stack->slots;
  while (stack->top >= slots)
    kod_stack_inplace_pop(stack, mem);
  kod_memory_dealloc(mem, slots);
}

void kod_stack_inplace_push(KodStack *stack, KodValue val, KodStatus *status)
{
  kod_stack_inplace_push_value(stack, val, status);
  if (!status->isOk)
    return;
  kod_value_retain(val);
}

void kod_stack_inplace_push_value(KodStack *stack, KodValue val, KodStatus *status)
{
  if (stack->top == stack->end)
  {
    kod_status_error(status, "stack overflow");
    return;
  }
  ++stack->top;
  stack->top[0] = val;
}

void kod_stack_inplace_push_object(KodStack *stack, KodValue val, KodStatus *status)
{
  kod_stack_inplace_push_value(stack, val, status);
  if (!status->isOk)
    return;
  kod_inc_ref(kod_as_object(val));
}

void kod_stack_inplace_pop(KodStack *stack, KodMemory *mem)
{
  kod_value_release(stack->top[0], mem);
  --stack->top;
}
