//
// string.h
//

#ifndef KOD_STRING_H
#define KOD_STRING_H

#include "value.h"

#define KOD_STRING_MIN_CAPACITY (1 << 3)
#define KOD_STRING_MAX_CAPACITY (1 << 30)

#define kod_string_clean(s) \
  do { \
    (s)->count = 0; \
    (s)->length = 0; \
    (s)->hash = -1; \
  } while (0)

typedef struct
{
  KodObject obj;
  int capacity;
  int count;
  int length;
  int64_t hash;
  char *chars;
} KodString;

KOD_API void kod_string_init(KodString *str, KodMemory *mem, KodStatus *status);
KOD_API void kod_string_init_with_capacity(KodString *str, int capacity, KodMemory *mem, KodStatus *status);
KOD_API void kod_string_init_from(KodString *str, const char *chars, KodMemory *mem, KodStatus *status);
KOD_API void kod_string_deinit(KodString *str, KodMemory *mem);
KOD_API KodString *kod_string_new(KodMemory *mem, KodStatus *status);
KOD_API KodString *kod_string_new_with_capacity(int capacity, KodMemory *mem, KodStatus *status);
KOD_API KodString *kod_string_new_from(const char *chars, KodMemory *mem, KodStatus *status);
KOD_API void kod_string_free(KodString *str, KodMemory *mem);
KOD_API void kod_string_release(KodString *str, KodMemory *mem);
KOD_API uint32_t kod_string_hash(KodString *str);
KOD_API bool kod_string_equal(KodString *str1, KodString *str2);
KOD_API int kod_string_compare(KodString *str1, KodString *str2);

#endif // KOD_STRING_H
