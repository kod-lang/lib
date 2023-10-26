//
// stack.h
//

#ifndef KOD_STACK_H
#define KOD_STACK_H

#include "memory.h"

#define KOD_STACK_DEFAULT_SIZE (1 << 10)

#define KodStack(T) \
  struct { \
    int size; \
    T *elements; \
    T *top; \
    T *end; \
  }

#define kod_stack_init(stk, sz, m, s) \
  do { \
    size_t size = sizeof(*(stk)->elements) * (sz); \
    void *elements = kod_memory_alloc((m), size, (s)); \
    if (!(s)->isOk) \
      break; \
    (stk)->size = (sz); \
    (stk)->elements = elements; \
    (stk)->top = &(stk)->elements[-1]; \
    (stk)->end = &(stk)->elements[(sz) - 1]; \
  } while (0)

#define kod_stack_deinit(stk, m) \
  do { \
    kod_memory_dealloc((m), (stk)->elements); \
  } while (0)

#define kod_stack_is_empty(s) ((s)->top == &(s)->elements[-1])

#define kod_stack_is_full(s) ((s)->top == (s)->end)

#define kod_stack_peek(s, i) ((s)->top[-(i)])

#define kod_stack_inplace_push(stk, e, s) \
  do { \
    if ((stk)->top == (stk)->end) { \
      kod_status_error((s), "stack overflow"); \
      break; \
    } \
    ++(stk)->top; \
    (stk)->top[0] = (e); \
  } while (0)

#define kod_stack_inplace_pop(stk, m) \
  do { \
    --(stk)->top; \
  } while (0)

#endif // KOD_STACK_H
