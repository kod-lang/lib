//
// stack.h
//

#ifndef KOD_STACK_H
#define KOD_STACK_H

//#include "value.h"
#include "memory.h"

#define KOD_STACK_DEFAULT_SIZE (1 << 10)

#define KodStack(T) \
  struct { \
    int size; \
    T *slots; \
    T *top; \
    T *end; \
  }

#define kod_stack_init(stk, sz, m, s) \
  do { \
    KodValue *slots = kod_memory_alloc((m), sizeof(*slots) * (sz), (s)); \
    if (!(s)->isOk) \
      break; \
    (stk)->size = (sz); \
    (stk)->slots = slots; \
    (stk)->top = &slots[-1]; \
    (stk)->end = &slots[(sz) - 1]; \
  } while (0)

#define kod_stack_deinit(stk, m) \
  do { \
    while ((stk)->top >= (stk)->slots) { \
      kod_value_release((stk)->top[0], (m)); \
      --(stk)->top; \
    } \
    kod_memory_dealloc((m), (stk)->slots); \
  } while (0)

#define kod_stack_is_empty(s) ((s)->top == &(s)->slots[-1])

#define kod_stack_is_full(s) ((s)->top == (s)->end)

#define kod_stack_peek(s, i) ((s)->top[-(i)])

#define kod_stack_inplace_push(stk, v, s) \
  do { \
    kod_stack_inplace_push_value((stk), (v), (s)); \
    if (!(s)->isOk) \
      break; \
    kod_value_retain((v)); \
  } while (0)

#define kod_stack_inplace_push_value(stk, v, s) \
  do { \
    if ((stk)->top == (stk)->end) { \
      kod_status_error((s), "stack overflow"); \
      break; \
    } \
    ++(stk)->top; \
    (stk)->top[0] = (v); \
  } while (0)

#define kod_stack_inplace_push_object(stk, v, s) \
  do { \
    kod_stack_inplace_push_value((stk), (v), (s)); \
    if (!(s)->isOk) \
      break; \
    kod_inc_ref(kod_as_object((v))); \
  } while (0)

#define kod_stack_inplace_pop(stk, m) \
  do { \
    kod_value_release((stk)->top[0], (m)); \
    --(stk)->top; \
  } while (0)

#endif // KOD_STACK_H
