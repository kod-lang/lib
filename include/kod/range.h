//
// range.h
//

#ifndef KOD_RANGE_H
#define KOD_RANGE_H

#include "value.h"

typedef struct
{
  KodObject obj;
  double from;
  double to;
} KodRange;

KOD_API void kod_range_init(KodRange *range, double from, double to);
KOD_API KodRange *kod_range_new(double from, double to, KodMemory *mem, KodStatus *status);
KOD_API void kod_range_dealloc(KodRange *range, KodMemory *mem);
KOD_API void kod_range_release(KodRange *range, KodMemory *mem);
KOD_API bool kod_range_equal(KodRange *range1, KodRange *range2);

#endif // KOD_RANGE_H
