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
  assert(!strcmp(kod_type_name(KOD_TYPE_NULL), "null"));
  assert(!strcmp(kod_type_name(KOD_TYPE_BOOLEAN), "boolean"));
  assert(!strcmp(kod_type_name(KOD_TYPE_NUMBER), "number"));
  assert(!strcmp(kod_type_name(KOD_TYPE_RUNE), "rune"));
  assert(!strcmp(kod_type_name(KOD_TYPE_STRING), "string"));
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
