//
// string.h
//

#ifndef KOD_STRING_H
#define KOD_STRING_H

#include "value.h"

typedef struct
{
  KodObject obj;
  int capacity;
  int count;
  int length;
  int64_t hash;
  char *chars;
} KodString;

KOD_API void kod_string_init(KodString *str);
KOD_API void kod_string_init_with_capacity(KodString *str, int capacity);
KOD_API void kod_string_deinit(KodString *str);
KOD_API KodString *kod_string_new(void);
KOD_API KodString *kod_string_new_with_capacity(int capacity);
KOD_API void kod_string_free(KodString *str);
KOD_API void kod_string_release(KodString *str);
KOD_API int kod_string_length(KodString *str);
KOD_API uint32_t kod_string_hash(KodString *str);

#endif // KOD_STRING_H
