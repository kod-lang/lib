//
// string.c
//

#include "kod/string.h"
#include <string.h>
#include "utils.h"

static inline void string_init_with_capacity(KodString *str, int capacity, KodMemory *mem, KodStatus *status);
static inline int string_check(int count, const char *chars, KodStatus *status);
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

static inline int string_check(int count, const char *chars, KodStatus *status)
{
  int length = 0;
  for (int i = 0; i < count;)
  {
    int n = rune_check(&chars[i], status);
    if (!status->isOk)
      return 0;
    if (!n)
      break;
    i += n;
    ++length;
  }
  return length;
}

static inline int rune_check(const char *runeChars, KodStatus *status)
{
  unsigned char *chars = (unsigned char *) runeChars;
  int n = rune_length(chars[0]);
  for (int i = 1; i < n; ++i)
    if ((chars[i] & 0xc0) != 0x80)
    {
      kod_status_error(status, "invalid UTF-8 encoding");
      return 0;
    }
  return n;
}

static inline int rune_length(unsigned char c)
{
  if ((c & 0xc0) == 0x80)
    return 0;
  if ((c & 0xf8) == 0xf0)
    return 4;
  if ((c & 0xf0) == 0xe0)
    return 3;
  if ((c & 0xe0) == 0xc0)
    return 2;
  return 1;  
}

static inline uint32_t string_hash(KodString *str)
{
  uint32_t hash = 2166136261;
  uint32_t *bytes = (uint32_t *) str->chars;
  for (int i = 0; i < str->count; ++i)
  {
    hash ^= bytes[i];
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
  if (capacity + 1 < KOD_STRING_MIN_CAPACITY)
  {
    string_init_with_capacity(str, KOD_STRING_MIN_CAPACITY, mem, status);
    return;
  }
  if (capacity + 1 > KOD_STRING_MAX_CAPACITY)
  {
    string_init_with_capacity(str, KOD_STRING_MAX_CAPACITY, mem, status);
    return;
  }
  string_init_with_capacity(str, power_of_two_ceil(capacity + 1), mem, status);
}

void kod_string_init_from(KodString *str, int count, const char *chars, KodMemory *mem, KodStatus *status)
{
  int length = string_check(count, (char *) chars, status);
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
    return NULL;
  return str;
}

KodString *kod_string_new_with_capacity(int capacity, KodMemory *mem, KodStatus *status)
{
  KodString *str = kod_memory_alloc(mem, sizeof(*str), status);
  if (!status->isOk)
    return NULL;
  kod_string_init_with_capacity(str, capacity, mem, status);
  if (!status->isOk)
    return NULL;
  return str;
}

KodString *kod_string_new_from(int count, const char *chars, KodMemory *mem, KodStatus *status)
{
  KodString *str = kod_memory_alloc(mem, sizeof(*str), status);
  if (!status->isOk)
    return NULL;
  kod_string_init_from(str, count, chars, mem, status);
  if (!status->isOk)
    return NULL;
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
