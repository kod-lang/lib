//
// range.c
//

#include "kod/range.h"

void kod_range_init(KodRange *range, double from, double to)
{
  kod_object_init(&range->obj);
  range->from = from;
  range->to = to;
}

KodRange *kod_range_new(double from, double to, KodMemory *mem, KodStatus *status)
{
  KodRange *range = kod_memory_alloc(mem, sizeof(*range), status);
  if (!status->isOk)
    return NULL;
  kod_range_init(range, from, to);
  return range;
}

void kod_range_dealloc(KodRange *range, KodMemory *mem)
{
  kod_memory_dealloc(mem, range);
}

void kod_range_release(KodRange *range, KodMemory *mem)
{
  KodObject *obj = &range->obj;
  kod_dec_ref(obj);
  if (kod_ref_count(obj))
    return;
  kod_range_dealloc(range, mem);
}

bool kod_range_equal(KodRange *range1, KodRange *range2)
{
  return (range1->from == range2->from) && (range1->to == range2->to);
}
