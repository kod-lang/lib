//
// vector.h
//

#ifndef KOD_VECTOR_H
#define KOD_VECTOR_H

#include "memory.h"
#include "utils.h"

#define KOD_VECTOR_MIN_CAPACITY (1 << 3)
#define KOD_VECTOR_MAX_CAPACITY (1 << 30)

#define KodVector(T) \
  struct { \
    int capacity; \
    int count; \
    T *elements; \
  }

#define kod_vector_init_with_capacity(v, c, m, s) \
  do { \
    int realCapacity = (c); \
    if (realCapacity > KOD_VECTOR_MAX_CAPACITY) { \
      kod_status_error((s), "vector capacity exceeds maximum"); \
      break; \
    } \
    realCapacity = (realCapacity < KOD_VECTOR_MIN_CAPACITY) ? \
      KOD_VECTOR_MIN_CAPACITY : kod_power_of_two_ceil(realCapacity); \
    size_t size = sizeof(*(v)->elements) * realCapacity; \
    void *elements = kod_memory_alloc((m), size, (s)); \
    if (!(s)->isOk) \
      break; \
    (v)->capacity = realCapacity; \
    (v)->count = 0; \
    (v)->elements = elements; \
  } while (0)

#define kod_vector_init(v, m, s) \
  do { \
    int capacity = KOD_VECTOR_MIN_CAPACITY; \
    size_t size = sizeof(*(v)->elements) * capacity; \
    void *elements = kod_memory_alloc((m), size, (s)); \
    if (!(s)->isOk) \
      break; \
    (v)->capacity = capacity; \
    (v)->count = 0; \
    (v)->elements = elements; \
  } while (0)

#define kod_vector_deinit(v, m) \
  do { \
    kod_memory_dealloc((m), (v)->elements); \
  } while (0)

#define kod_vector_get(v, i) ((v)->elements[(i)])

#define kod_vector_inplace_add(v, e, m, s) \
  do { \
    if ((v)->count == (v)->capacity) { \
      if ((v)->capacity == KOD_VECTOR_MAX_CAPACITY) { \
        kod_status_error((s), "vector capacity exceeds maximum"); \
        break; \
      } \
      int capacity = (v)->capacity << 1; \
      size_t size = sizeof(*(v)->elements) * capacity; \
      void *elements = kod_memory_realloc((m), (v)->elements, size, (s)); \
      if (!(s)->isOk) \
        break; \
      (v)->capacity = capacity; \
      (v)->elements = elements; \
    } \
    (v)->elements[(v)->count] = (e); \
    ++(v)->count; \
  } while (0)

#define kod_vector_inplace_set(v, i, e) \
  do { \
    (v)->elements[(i)] = (e); \
  } while (0)

#define kod_vector_inplace_remove_at(v, i) \
  do { \
    --(v)->count; \
    for (int j = (i); j < (v)->count; ++j) \
      (v)->elements[j] = (v)->elements[j + 1]; \
  } while (0)

#define kod_vector_inplace_clear(v) \
  do { \
    (v)->count = 0; \
  } while (0)

#endif // KOD_VECTOR_H
