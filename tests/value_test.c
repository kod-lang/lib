//
// value_test.c
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

static inline void value_type_name_test(void);
static inline void value_dealloc_test(void);
static inline void value_release_test(void);
static inline void value_equal_different_types_test(void);
static inline void value_equal_null_test(void);
static inline void value_equal_boolean_test(void);
static inline void value_equal_number_test(void);
static inline void value_equal_rune_test(void);
static inline void value_equal_string_test(void);
static inline void value_equal_reference_test(void);
static inline void value_compare_different_types_test(void);
static inline void value_compare_null_test(void);
static inline void value_compare_boolean_test(void);
static inline void value_compare_number_test(void);
static inline void value_compare_rune_test(void);
static inline void value_compare_string_test(void);
static inline void value_compare_reference_test(void);

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

static inline void value_type_name_test(void)
{
  assert(!strcmp(kod_type_name(KOD_TYPE_NULL), "null"));
  assert(!strcmp(kod_type_name(KOD_TYPE_BOOLEAN), "boolean"));
  assert(!strcmp(kod_type_name(KOD_TYPE_NUMBER), "number"));
  assert(!strcmp(kod_type_name(KOD_TYPE_RUNE), "rune"));
  assert(!strcmp(kod_type_name(KOD_TYPE_STRING), "string"));
  assert(!strcmp(kod_type_name(KOD_TYPE_REFERENCE), "reference"));
}

static inline void value_dealloc_test(void)
{
  kod_value_dealloc(KOD_NULL_VALUE, &mem);
  kod_value_dealloc(KOD_FALSE_VALUE, &mem);
  kod_value_dealloc(KOD_TRUE_VALUE, &mem);
  kod_value_dealloc(kod_number_value(1.23), &mem);
  kod_value_dealloc(kod_rune_value('a'), &mem);
  KodStatus status;
  kod_status_ok(&status);
  KodString *str = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  kod_value_dealloc(kod_string_value(str), &mem);
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
  val = kod_number_value(1.23);
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

static inline void value_equal_different_types_test(void)
{
  assert(!kod_value_equal(KOD_NULL_VALUE, KOD_FALSE_VALUE));
}

static inline void value_equal_null_test(void)
{
  assert(kod_value_equal(KOD_NULL_VALUE, KOD_NULL_VALUE));
}

static inline void value_equal_boolean_test(void)
{
  assert(kod_value_equal(KOD_FALSE_VALUE, KOD_FALSE_VALUE));
  assert(!kod_value_equal(KOD_FALSE_VALUE, KOD_TRUE_VALUE));
}

static inline void value_equal_number_test(void)
{
  assert(kod_value_equal(kod_number_value(1.23), kod_number_value(1.23)));
  assert(!kod_value_equal(kod_number_value(1.23), kod_number_value(2.34)));
}

static inline void value_equal_rune_test(void)
{
  assert(kod_value_equal(kod_rune_value('a'), kod_rune_value('a')));
  assert(!kod_value_equal(kod_rune_value('a'), kod_rune_value('b')));
}

static inline void value_equal_string_test(void)
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
  assert(kod_value_equal(kod_string_value(&str1), kod_string_value(&str1)));
  assert(kod_value_equal(kod_string_value(&str1), kod_string_value(&str2)));
  assert(!kod_value_equal(kod_string_value(&str1), kod_string_value(&str3)));
  kod_string_deinit(&str1, &mem);
  kod_string_deinit(&str2, &mem);
  kod_string_deinit(&str3, &mem);
}

static inline void value_equal_reference_test(void)
{
  KodValue val1;
  KodValue val2;
  assert(kod_value_equal(kod_reference_value(&val1), kod_reference_value(&val1)));
  assert(!kod_value_equal(kod_reference_value(&val1), kod_reference_value(&val2)));
}

static inline void value_compare_different_types_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  (void) kod_value_compare(KOD_NULL_VALUE, KOD_FALSE_VALUE, &status);
  assert(!status.isOk);
  assert(!strcmp(status.error, "cannot compare null and boolean values"));
}

static inline void value_compare_null_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  int cmp = kod_value_compare(KOD_NULL_VALUE, KOD_NULL_VALUE, &status);
  assert(status.isOk);
  assert(!cmp);
}

static inline void value_compare_boolean_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  int cmp;
  cmp = kod_value_compare(KOD_FALSE_VALUE, KOD_FALSE_VALUE, &status);
  assert(status.isOk);
  assert(!cmp);
  cmp = kod_value_compare(KOD_FALSE_VALUE, KOD_TRUE_VALUE, &status);
  assert(status.isOk);
  assert(cmp < 0);
  cmp = kod_value_compare(KOD_TRUE_VALUE, KOD_FALSE_VALUE, &status);
  assert(status.isOk);
  assert(cmp > 0);
}

static inline void value_compare_number_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  int cmp;
  cmp = kod_value_compare(kod_number_value(1.23), kod_number_value(1.23), &status);
  assert(status.isOk);
  assert(!cmp);
  cmp = kod_value_compare(kod_number_value(1.23), kod_number_value(2.34), &status);
  assert(status.isOk);
  assert(cmp < 0);
  cmp = kod_value_compare(kod_number_value(2.34), kod_number_value(1.23), &status);
  assert(status.isOk);
  assert(cmp > 0);
}

static inline void value_compare_rune_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  int cmp;
  cmp = kod_value_compare(kod_rune_value('a'), kod_rune_value('a'), &status);
  assert(status.isOk);
  assert(!cmp);
  cmp = kod_value_compare(kod_rune_value('a'), kod_rune_value('b'), &status);
  assert(status.isOk);
  assert(cmp < 0);
  cmp = kod_value_compare(kod_rune_value('b'), kod_rune_value('a'), &status);
  assert(status.isOk);
  assert(cmp > 0);
}

static inline void value_compare_string_test(void)
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
  int cmp;
  cmp = kod_value_compare(kod_string_value(&str1), kod_string_value(&str1), &status);
  assert(status.isOk);
  assert(!cmp);
  cmp = kod_value_compare(kod_string_value(&str1), kod_string_value(&str2), &status);
  assert(status.isOk);
  assert(!cmp);
  cmp = kod_value_compare(kod_string_value(&str1), kod_string_value(&str3), &status);
  assert(status.isOk);
  assert(cmp > 0);
  cmp = kod_value_compare(kod_string_value(&str3), kod_string_value(&str1), &status);
  assert(status.isOk);
  assert(cmp < 0);
  kod_string_deinit(&str1, &mem);
  kod_string_deinit(&str2, &mem);
  kod_string_deinit(&str3, &mem);
}

static inline void value_compare_reference_test(void)
{
  KodValue val1;
  KodValue val2;
  KodStatus status;
  kod_status_ok(&status);
  int cmp;
  cmp = kod_value_compare(kod_reference_value(&val1), kod_reference_value(&val1), &status);
  assert(status.isOk);
  assert(!cmp);
  cmp = kod_value_compare(kod_reference_value(&val1), kod_reference_value(&val2), &status);
  assert(status.isOk);
  assert(cmp);
}

int main(void)
{
  value_type_name_test();
  value_dealloc_test();
  value_release_test();
  value_equal_different_types_test();
  value_equal_null_test();
  value_equal_boolean_test();
  value_equal_number_test();
  value_equal_rune_test();
  value_equal_string_test();
  value_equal_reference_test();
  value_compare_different_types_test();
  value_compare_null_test();
  value_compare_boolean_test();
  value_compare_number_test();
  value_compare_rune_test();
  value_compare_string_test();
  value_compare_reference_test();
  return EXIT_SUCCESS;
}
