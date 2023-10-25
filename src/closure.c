//
// closure.c
//

#include "kod/closure.h"

void kod_closure_init(KodClosure *cl, KodFunction *fn, KodMemory *mem, KodStatus *status)
{
  int numNonlocals = fn->nonlocals.count;
  KodValue *nonlocals = kod_memory_alloc(mem, sizeof(*nonlocals) * numNonlocals, status);
  if (!status->isOk)
    return;
  for (int i = 0; i < numNonlocals; ++i)
    nonlocals[i] = KOD_NULL_VALUE;
  kod_object_init(&cl->obj);
  cl->fn = fn;
  kod_inc_ref(&fn->obj);
  cl->nonlocals = nonlocals;
}

void kod_closure_deinit(KodClosure *cl, KodMemory *mem)
{
  KodFunction *fn = cl->fn;
  int numNonlocals = fn->nonlocals.count;
  kod_function_release(fn, mem);
  KodValue *nonlocals = cl->nonlocals;
  for (int i = 0; i < numNonlocals; ++i)
    kod_value_release(nonlocals[i], mem);
  kod_memory_dealloc(mem, nonlocals);
}

KodClosure *kod_closure_new(KodFunction *fn, KodMemory *mem, KodStatus *status)
{
  KodClosure *cl = kod_memory_alloc(mem, sizeof(*cl), status);
  if (!status->isOk)
    return NULL;
  kod_closure_init(cl, fn, mem, status);
  if (!status->isOk)
  {
    kod_memory_dealloc(mem, cl);
    return NULL;
  }
  return cl;
}

void kod_closure_dealloc(KodClosure *cl, KodMemory *mem)
{
  kod_closure_deinit(cl, mem);
  kod_memory_dealloc(mem, cl);
}

void kod_closure_release(KodClosure *cl, KodMemory *mem)
{
  KodObject *obj = &cl->obj;
  kod_dec_ref(obj);
  if (kod_ref_count(obj))
    return;
  kod_closure_dealloc(cl, mem);
}
