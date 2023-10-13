//
// value_test.c
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "kod/string.h"

static void *memory_alloc(size_t size, void *udata);
static void *memory_realloc(void *ptr, size_t size, void *udata);
static void memory_free(void *ptr, void *udata);

static KodMemory mem = {
  .alloc = memory_alloc,
  .realloc = memory_realloc,
  .free = memory_free,
  .udata = NULL
};

static inline void value_type_name_test(void);
static inline void value_free_test(void);
static inline void value_release_test(void);

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

static void memory_free(void *ptr, void *udata)
{
  (void) udata;
  free(ptr);
}

static inline void value_type_name_test(void)
{
  assert(!strcmp(kod_type_name(KOD_TYPE_NULL), "null"));
  assert(!strcmp(kod_type_name(KOD_TYPE_BOOLEAN), "boolean"));
  assert(!strcmp(kod_type_name(KOD_TYPE_NUMBER), "number"));
  assert(!strcmp(kod_type_name(KOD_TYPE_RUNE), "rune"));
  assert(!strcmp(kod_type_name(KOD_TYPE_STRING), "string"));
}

static inline void value_free_test(void)
{
  kod_value_free(KOD_NULL_VALUE, &mem);
  kod_value_free(KOD_FALSE_VALUE, &mem);
  kod_value_free(KOD_TRUE_VALUE, &mem);
  kod_value_free(kod_number_value(0), &mem);
  kod_value_free(kod_rune_value('a'), &mem);
  KodStatus status;
  kod_status_ok(&status);
  KodString *str = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  kod_value_free(kod_string_value(str), &mem);
}

static inline void value_release_test(void)
{
  KodValue val;
  val = KOD_NULL_VALUE;
  kod_value_retain(val);
  kod_value_release(val, &mem);
  val = KOD_FALSE_VALUE;
  kod_value_retain(val);
  kod_value_release(val, &mem);
  val = KOD_TRUE_VALUE;
  kod_value_retain(val);
  kod_value_release(val, &mem);
  val = kod_number_value(0);
  kod_value_retain(val);
  kod_value_release(val, &mem);
  val = kod_rune_value('a');
  kod_value_retain(val);
  kod_value_release(val, &mem);
  KodStatus status;
  kod_status_ok(&status);
  KodString *str = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  val = kod_string_value(str);
  kod_value_retain(val);
  kod_value_release(val, &mem);
}

int main(void)
{
  value_type_name_test();
  value_free_test();
  value_release_test();
  return EXIT_SUCCESS;
}
