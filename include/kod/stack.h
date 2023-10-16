//
// stack.h
//

#ifndef KOD_STACK_H
#define KOD_STACK_H

#include "value.h"

#define KOD_STACK_DEFAULT_SIZE (1 << 10)

#define kod_stack_is_empty(s) ((s)->top == &(s)->slots[-1])
#define kod_stack_is_full(s)  ((s)->top == (s)->end)
#define kod_stack_peek(s, i)  ((s)->top[-(i)])

typedef struct
{
  int size;
  KodValue *slots;
  KodValue *top;
  KodValue *end;
} KodStack;

void kod_stack_init(KodStack *stack, int size, KodMemory *mem, KodStatus *status);
void kod_stack_deinit(KodStack *stack, KodMemory *mem);
void kod_stack_inplace_push(KodStack *stack, KodValue val, KodStatus *status);
void kod_stack_inplace_push_value(KodStack *stack, KodValue val, KodStatus *status);
void kod_stack_inplace_push_object(KodStack *stack, KodValue val, KodStatus *status);
void kod_stack_inplace_pop(KodStack *stack, KodMemory *mem);

#endif // KOD_STACK_H
