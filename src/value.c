//
// value.c
//

#include "kod/value.h"
#include "kod/string.h"

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
  case KOD_TYPE_REFERENCE:
    name = "reference";
    break;
  }
  return name;
}

void kod_value_free(KodValue val, KodMemory *mem)
{
  switch (kod_type(val))
  {
  case KOD_TYPE_NULL:
  case KOD_TYPE_BOOLEAN:
  case KOD_TYPE_NUMBER:
  case KOD_TYPE_RUNE:
  case KOD_TYPE_REFERENCE:
    break;
  case KOD_TYPE_STRING:
    kod_string_free(kod_as_string(val), mem);
  }
}

void kod_value_release(KodValue val, KodMemory *mem)
{
  switch (kod_type(val))
  {
  case KOD_TYPE_NULL:
  case KOD_TYPE_BOOLEAN:
  case KOD_TYPE_NUMBER:
  case KOD_TYPE_RUNE:
  case KOD_TYPE_REFERENCE:
    break;
  case KOD_TYPE_STRING:
    kod_string_release(kod_as_string(val), mem);
  }
}
