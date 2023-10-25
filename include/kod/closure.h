//
// closure.h
//

#ifndef KOD_CLOSURE_H
#define KOD_CLOSURE_H

#include "function.h"

typedef struct
{
  KodObject obj;
  KodFunction *fn;
  KodValue *nonlocals;
} KodClosure;

KOD_API void kod_closure_init(KodClosure *cl, KodFunction *fn, KodMemory *mem, KodStatus *status);
KOD_API void kod_closure_deinit(KodClosure *cl, KodMemory *mem);
KOD_API KodClosure *kod_closure_new(KodFunction *fn, KodMemory *mem, KodStatus *status);
KOD_API void kod_closure_dealloc(KodClosure *cl, KodMemory *mem);
KOD_API void kod_closure_release(KodClosure *cl, KodMemory *mem);

#endif // KOD_CLOSURE_H
