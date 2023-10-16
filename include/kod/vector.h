//
// vector.h
//

#ifndef KOD_VECTOR_H
#define KOD_VECTOR_H

#include "memory.h"

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
    size_t size = sizeof(*(v)->elements) * (c); \
    void *elements = kod_memory_alloc((m), size, (s)); \
    if (!(s)->isOk) \
      break; \
    (v)->capacity = (c); \
    (v)->count = 0; \
    (v)->elements = elements; \
  } while (0)

#define kod_vector_init(v, m, s) \
  do { \
    kod_vector_init_with_capacity((v), KOD_VECTOR_MIN_CAPACITY, (m), (s)); \
  } while (0)

#define kod_vector_deinit(v, m) \
  do { \
    kod_memory_dealloc((m), (v)->elements); \
  } while (0)

#define kod_vector_get(v, i) ((v)->elements[(i)])

#define kod_vector_inplace_add(v, e, m, s) \
  do { \
    if ((v)->count == (v)->capacity) { \
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

#define kod_vector_inplace_clean(v) \
  do { \
    (v)->count = 0; \
  } while (0)

#endif // KOD_VECTOR_H
