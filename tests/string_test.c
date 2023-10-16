//
// string_test.c
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "kod/string.h"

static void *memory_alloc(size_t size, void *udata);
static void *memory_realloc(void *ptr, size_t size, void *udata);
static void memory_dealloc(void *ptr, void *udata);

static KodMemory mem = {
  .alloc = memory_alloc,
  .realloc = memory_realloc,
  .dealloc = memory_dealloc,
  .udata = NULL
};

static inline void string_init_test(void);
static inline void string_init_with_capacity_test(void);
static inline void string_init_with_capacity_less_than_min_test(void);
static inline void string_init_with_capacity_greater_than_max_test(void);
static inline void string_init_from_ascii_test(void);
static inline void string_init_from_utf8_test(void);
static inline void string_new_test(void);
static inline void string_new_with_capacity_test(void);
static inline void string_new_from_ascii_test(void);
static inline void string_new_from_utf8_test(void);
static inline void string_release_test(void);
static inline void string_hash_test(void);
static inline void string_equal_test(void);
static inline void string_compare_test(void);

static void *memory_alloc(size_t size, void *udata)
{
  (void) udata;
  return malloc(size);
}

static void *memory_realloc(void *ptr, size_t size, void *udata)
{
  (void) udata;
  return realloc(ptr, size);
}

static void memory_dealloc(void *ptr, void *udata)
{
  (void) udata;
  free(ptr);
}

static inline void string_init_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString str;
  kod_string_init(&str, &mem, &status);
  assert(status.isOk);
  assert(!str.obj.refCount);
  assert(str.capacity == KOD_STRING_MIN_CAPACITY);
  assert(!str.count);
  assert(!str.length);
  assert(str.hash == -1);
  assert(str.chars);
  kod_string_deinit(&str, &mem);
}

static inline void string_init_with_capacity_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString str;
  kod_string_init_with_capacity(&str, 8, &mem, &status);
  assert(status.isOk);
  assert(str.capacity == 16);
  kod_string_deinit(&str, &mem);
}

static inline void string_init_with_capacity_less_than_min_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString str;
  kod_string_init_with_capacity(&str, KOD_STRING_MIN_CAPACITY - 1, &mem, &status);
  assert(status.isOk);
  assert(str.capacity == KOD_STRING_MIN_CAPACITY);
  kod_string_deinit(&str, &mem);
}

static inline void string_init_with_capacity_greater_than_max_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString str;
  kod_string_init_with_capacity(&str, KOD_STRING_MAX_CAPACITY + 1, &mem, &status);
  assert(!status.isOk);
  assert(!strcmp(status.error, "string capacity exceeds maximum"));
}

static inline void string_init_from_ascii_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString str;
  kod_string_init_from(&str, "foo", &mem, &status);
  assert(status.isOk);
  assert(!strcmp(str.chars, "foo"));
  assert(str.count == 3);
  assert(str.length == 3);
}

static inline void string_init_from_utf8_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString str;
  kod_string_init_from(&str, "\xF0\x9F\x98\x81", &mem, &status);
  assert(status.isOk);
  assert(!strcmp(str.chars, "\xF0\x9F\x98\x81"));
  assert(str.count == 4);
  assert(str.length == 1);
}

static inline void string_new_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *str = kod_string_new(&mem, &status);
  assert(status.isOk);
  assert(!str->obj.refCount);
  assert(str->capacity == KOD_STRING_MIN_CAPACITY);
  assert(!str->count);
  assert(!str->length);
  assert(str->hash == -1);
  assert(str->chars);
  kod_string_dealloc(str, &mem);
}

static inline void string_new_with_capacity_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *str = kod_string_new_with_capacity(8, &mem, &status);
  assert(status.isOk);
  assert(str->capacity == 16);
  kod_string_dealloc(str, &mem);
}

static inline void string_new_from_ascii_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *str = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  assert(!strcmp(str->chars, "foo"));
  assert(str->count == 3);
  assert(str->length == 3);
  kod_string_dealloc(str, &mem);
}

static inline void string_new_from_utf8_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *str = kod_string_new_from("\xF0\x9F\x98\x81", &mem, &status);
  assert(status.isOk);
  assert(!strcmp(str->chars, "\xF0\x9F\x98\x81"));
  assert(str->count == 4);
  assert(str->length == 1);
  kod_string_dealloc(str, &mem);
}

static inline void string_release_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString *str = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  kod_inc_ref(&str->obj);
  kod_string_release(str, &mem);
}

static inline void string_hash_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodString str;
  kod_string_init_from(&str, "foo", &mem, &status);
  assert(status.isOk);
  uint32_t expected = 0xa9f37ed7;
  uint32_t hash = kod_string_hash(&str);
  assert((uint32_t) str.hash == expected);
  assert(hash == expected);
  kod_string_deinit(&str, &mem);
}

static inline void string_equal_test(void)
{
  KodString str1;
  KodString str2;
  KodString str3;
  KodStatus status;
  kod_status_ok(&status);
  kod_string_init_from(&str1, "foo", &mem, &status);
  assert(status.isOk);
  kod_string_init_from(&str2, "foo", &mem, &status);
  assert(status.isOk);
  kod_string_init_from(&str3, "bar", &mem, &status);
  assert(status.isOk);
  assert(kod_string_equal(&str1, &str2));
  assert(!kod_string_equal(&str1, &str3));
  kod_string_deinit(&str1, &mem);
  kod_string_deinit(&str2, &mem);
  kod_string_deinit(&str3, &mem);
}

static inline void string_compare_test(void)
{
  KodString str1;
  KodString str2;
  KodString str3;
  KodStatus status;
  kod_status_ok(&status);
  kod_string_init_from(&str1, "foo", &mem, &status);
  assert(status.isOk);
  kod_string_init_from(&str2, "foo", &mem, &status);
  assert(status.isOk);
  kod_string_init_from(&str3, "bar", &mem, &status);
  assert(status.isOk);
  assert(!kod_string_compare(&str1, &str2));
  assert(kod_string_compare(&str1, &str3) > 0);
  assert(kod_string_compare(&str3, &str1) < 0);
  kod_string_deinit(&str1, &mem);
  kod_string_deinit(&str2, &mem);
  kod_string_deinit(&str3, &mem);
}

int main(void)
{
  string_init_test();
  string_init_with_capacity_test();
  string_init_with_capacity_less_than_min_test();
  string_init_with_capacity_greater_than_max_test();
  string_init_from_ascii_test();
  string_init_from_utf8_test();
  string_new_test();
  string_new_with_capacity_test();
  string_new_from_ascii_test();
  string_new_from_utf8_test();
  string_release_test();
  string_hash_test();
  string_equal_test();
  string_compare_test();
  return EXIT_SUCCESS;
}
