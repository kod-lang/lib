//
// value_test.c
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "kod/value.h"

static inline void value_type_name_test(void);
static inline void value_retain_release_test(void);

static inline void value_type_name_test(void)
{
  KodValue val;
  val = KOD_NULL_VALUE;
  assert(!strcmp(kod_type_name(kod_type(val)), "null"));
  val = KOD_FALSE_VALUE;
  assert(!strcmp(kod_type_name(kod_type(val)), "boolean"));
  val = KOD_TRUE_VALUE;
  assert(!strcmp(kod_type_name(kod_type(val)), "boolean"));
  val = kod_number_value(0);
  assert(!strcmp(kod_type_name(kod_type(val)), "number"));
  val = kod_rune_value(0);
  assert(!strcmp(kod_type_name(kod_type(val)), "rune"));
  val = kod_string_value(NULL);
  assert(!strcmp(kod_type_name(kod_type(val)), "string"));
}

static inline void value_retain_release_test(void)
{
  // TODO: Implement this function.
  assert(1);
}

int main(void)
{
  value_type_name_test();
  value_retain_release_test();
  return EXIT_SUCCESS;
}
