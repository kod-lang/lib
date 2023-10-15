//
// string.c
//

#include "kod/string.h"
#include <string.h>
#include "utils.h"

static inline void string_init_with_capacity(KodString *str, int capacity, KodMemory *mem, KodStatus *status);
static inline void string_check(const char *chars, int *count, int *length, KodStatus *status);
static inline int rune_check(const char *runeChars, KodStatus *status);
static inline int rune_length(unsigned char c);
static inline uint32_t string_hash(KodString *str);

static inline void string_init_with_capacity(KodString *str, int capacity, KodMemory *mem, KodStatus *status)
{
  char *chars = kod_memory_alloc(mem, capacity, status);
  if (!status->isOk)
    return;
  kod_object_init(&str->obj);
  str->capacity = capacity;
  str->count = 0;
  str->length = 0;
  str->hash = -1;
  str->chars = chars;
}

static inline void string_check(const char *chars, int *count, int *length, KodStatus *status)
{
  int i = 0;
  int j = 0;
  for (;;)
  {
    const char *runeChars = &chars[i];
    if (!runeChars[0])
      break;
    int n = rune_check(runeChars, status);
    if (!status->isOk)
      return;
    i += n;
    ++j;
  }
  *count = i;
  *length = j;
}

static inline int rune_check(const char *runeChars, KodStatus *status)
{
  unsigned char *chars = (unsigned char *) runeChars;
  int n = rune_length(chars[0]);
  if (!n)
    goto error;
  for (int i = 1; i < n; ++i)
    if ((chars[i] & 0xc0) != 0x80)
      goto error;
  return n;
error:
  kod_status_error(status, "invalid UTF-8 encoding");
  return 0;
}

static inline int rune_length(unsigned char c)
{
  if ((c & 0x80) == 0)
    return 1;
  if ((c & 0xe0) == 0xc0)
    return 2;
  if ((c & 0xf0) == 0xe0)
    return 3;
  if ((c & 0xf8) == 0xf0)
    return 4;
  return 0;
}

static inline uint32_t string_hash(KodString *str)
{
  uint32_t hash = 2166136261;
  for (int i = 0; i < str->count; ++i)
  {
    hash ^= str->chars[i];
    hash *= 16777619;
  }
  return hash;
}

void kod_string_init(KodString *str, KodMemory *mem, KodStatus *status)
{
  string_init_with_capacity(str, KOD_STRING_MIN_CAPACITY, mem, status);
}

void kod_string_init_with_capacity(KodString *str, int capacity, KodMemory *mem, KodStatus *status)
{
  int realCapacity = capacity + 1;
  if (realCapacity > KOD_STRING_MAX_CAPACITY)
  {
    kod_status_error(status, "string capacity exceeds maximum");
    return;
  }
  realCapacity = (realCapacity < KOD_STRING_MIN_CAPACITY) ? 
    KOD_STRING_MIN_CAPACITY : power_of_two_ceil(realCapacity);
  string_init_with_capacity(str, realCapacity, mem, status);
}

void kod_string_init_from(KodString *str, const char *chars, KodMemory *mem, KodStatus *status)
{
  int count;
  int length;
  string_check(chars, &count, &length, status);
  if (!status->isOk)
    return;
  kod_string_init_with_capacity(str, length, mem, status);
  if (!status->isOk)
    return;
  str->count = count;
  str->length = length;
  memcpy(str->chars, chars, count);
  str->chars[count] = '\0';
}

void kod_string_deinit(KodString *str, KodMemory *mem)
{
  kod_memory_free(mem, str->chars);
}

KodString *kod_string_new(KodMemory *mem, KodStatus *status)
{
  KodString *str = kod_memory_alloc(mem, sizeof(*str), status);
  if (!status->isOk)
    return NULL;
  kod_string_init(str, mem, status);
  if (!status->isOk)
  {
    kod_memory_free(mem, str);
    return NULL;
  }
  return str;
}

KodString *kod_string_new_with_capacity(int capacity, KodMemory *mem, KodStatus *status)
{
  KodString *str = kod_memory_alloc(mem, sizeof(*str), status);
  if (!status->isOk)
    return NULL;
  kod_string_init_with_capacity(str, capacity, mem, status);
  if (!status->isOk)
  {
    kod_memory_free(mem, str);
    return NULL;
  }
  return str;
}

KodString *kod_string_new_from(const char *chars, KodMemory *mem, KodStatus *status)
{
  KodString *str = kod_memory_alloc(mem, sizeof(*str), status);
  if (!status->isOk)
    return NULL;
  kod_string_init_from(str, chars, mem, status);
  if (!status->isOk)
  {
    kod_memory_free(mem, str);
    return NULL;
  }
  return str;
}

void kod_string_free(KodString *str, KodMemory *mem)
{
  kod_string_deinit(str, mem);
  kod_memory_free(mem, str);
}

void kod_string_release(KodString *str, KodMemory *mem)
{
  KodObject *obj = &str->obj;
  kod_dec_ref(obj);
  if (kod_ref_count(obj))
    return;
  kod_string_free(str, mem);
}

uint32_t kod_string_hash(KodString *str)
{
  if (str->hash == -1)
    str->hash = string_hash(str);
  return (uint32_t) str->hash;
}

bool kod_string_equal(KodString *str1, KodString *str2)
{
  if (str1->count != str2->count)
    return false;
  return !strncmp(str1->chars, str2->chars, str1->count);
}

int kod_string_compare(KodString *str1, KodString *str2)
{
  int minCount = (str1->count < str2->count) ? str1->count : str2->count;
  int cmp = strncmp(str1->chars, str2->chars, minCount);
  if (cmp)
    return cmp;
  return str1->count - str2->count;
}
