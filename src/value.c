//
// value.c
//

#include "kod/value.h"
#include <stddef.h>

const char *kod_type_name(KodType type)
{
  char *name = "null";
  switch (type)
  {
  case KOD_TYPE_NULL:
    break;
  case KOD_TYPE_BOOLEAN:
    name = "boolean";
    break;
  case KOD_TYPE_NUMBER:
    name = "number";
    break;
  case KOD_TYPE_RUNE:
    name = "rune";
    break;
  case KOD_TYPE_STRING:
    name = "string";
    break;
  }
  return name;
}

void kod_value_release(KodValue val)
{
  // TODO: Implement this function.
  (void) val;
}
