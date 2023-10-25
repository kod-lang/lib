//
// value.c
//

#include "kod/value.h"
#include <math.h>
#include "kod/closure.h"
#include "kod/range.h"

#define EPSILON 1e-9

static inline int number_compare(double num1, double num2);

static inline int number_compare(double num1, double num2)
{
  if (fabs(num1 - num2) < EPSILON)
    return 0;
  return (num1 < num2) ? -1 : 1;
}

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
  case KOD_TYPE_RANGE:
    name = "range";
    break;
  case KOD_TYPE_CLOSURE:
    name = "closure";
    break;
  case KOD_TYPE_REFERENCE:
    name = "reference";
    break;
  }
  return name;
}

void kod_value_dealloc(KodValue val, KodMemory *mem)
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
    kod_string_dealloc(kod_as_string(val), mem);
    break;
  case KOD_TYPE_RANGE:
    kod_range_dealloc(kod_as_range(val), mem);
    break;
  case KOD_TYPE_CLOSURE:
    kod_closure_dealloc(kod_as_closure(val), mem);
    break;
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
    break;
  case KOD_TYPE_RANGE:
    kod_range_release(kod_as_range(val), mem);
    break;
  case KOD_TYPE_CLOSURE:
    kod_closure_release(kod_as_closure(val), mem);
    break;
  }
}

bool kod_value_equal(KodValue val1, KodValue val2)
{
  if (kod_type(val1) != kod_type(val2))
    return false;
  bool isEqual = true;
  switch (kod_type(val1))
  {
  case KOD_TYPE_NULL:
    break;
  case KOD_TYPE_BOOLEAN:
    isEqual = kod_as_boolean(val1) == kod_as_boolean(val2);
    break;
  case KOD_TYPE_NUMBER:
    isEqual = fabs(kod_as_number(val1) - kod_as_number(val2)) < EPSILON;
    break;
  case KOD_TYPE_RUNE:
    isEqual = kod_as_rune(val1) == kod_as_rune(val2);
    break;
  case KOD_TYPE_STRING:
    isEqual = kod_string_equal(kod_as_string(val1), kod_as_string(val2));
    break;
  case KOD_TYPE_RANGE:
    isEqual = kod_range_equal(kod_as_range(val1), kod_as_range(val2));
    break;
  case KOD_TYPE_CLOSURE:
  case KOD_TYPE_REFERENCE:
    isEqual = val1.asPointer == val2.asPointer;
    break;
  }
  return isEqual;
}

int kod_value_compare(KodValue val1, KodValue val2, KodStatus *status)
{
  if (kod_type(val1) != kod_type(val2))
  {
    kod_status_error(status, "cannot compare %s and %s values", kod_type_name(kod_type(val1)),
      kod_type_name(kod_type(val2)));
    return 0;
  }
  int cmp = 0;
  switch (kod_type(val1))
  {
  case KOD_TYPE_NULL:
    break;
  case KOD_TYPE_BOOLEAN:
    cmp = kod_as_boolean(val1) - kod_as_boolean(val2);
    break;
  case KOD_TYPE_NUMBER:
    cmp = number_compare(kod_as_number(val1), kod_as_number(val2));
    break;
  case KOD_TYPE_RUNE:
    cmp = (int) (kod_as_rune(val1) - kod_as_rune(val2));
    break;
  case KOD_TYPE_STRING:
    cmp = kod_string_compare(kod_as_string(val1), kod_as_string(val2));
    break;
  case KOD_TYPE_RANGE:
  case KOD_TYPE_CLOSURE:
  case KOD_TYPE_REFERENCE:
    kod_status_error(status, "cannot compare %s values", kod_type_name(kod_type(val1)));
    break;
  }
  return cmp;
}
