//
// function.c
//

#include "kod/function.h"

void kod_function_init(KodFunction *fn, uint8_t arity, KodString *name, KodString *file,
  KodMemory *mem, KodStatus *status)
{
  kod_object_init(&fn->obj);
  fn->arity = arity;
  fn->name = name;
  kod_inc_ref(&name->obj);
  fn->file = file;
  kod_inc_ref(&file->obj);
  kod_chunk_init(&fn->chunk, mem, status);
  if (!status->isOk)
    return;
  kod_vector_init(&fn->nonlocals, mem, status);
  if (!status->isOk)
  {
    kod_chunk_deinit(&fn->chunk, mem);
    return;
  }
  kod_vector_init(&fn->functions, mem, status);
  if (status->isOk)
    return;
  kod_chunk_deinit(&fn->chunk, mem);
  kod_vector_deinit(&fn->nonlocals, mem);
}

void kod_function_deinit(KodFunction *fn, KodMemory *mem)
{
  kod_string_release(fn->name, mem);
  kod_string_release(fn->file, mem);
  kod_chunk_deinit(&fn->chunk, mem);
  kod_vector_deinit(&fn->nonlocals, mem);
  for (int i = 0; i < fn->functions.count; ++i)
  {
    KodFunction *child = kod_vector_get(&fn->functions, i);
    kod_function_release(child, mem);
  }
  kod_vector_deinit(&fn->functions, mem);
}

KodFunction *kod_function_new(uint8_t arity, KodString *name, KodString *file,
  KodMemory *mem, KodStatus *status)
{
  KodFunction *fn = kod_memory_alloc(mem, sizeof(*fn), status);
  if (!status->isOk)
    return NULL;
  kod_function_init(fn, arity, name, file, mem, status);
  if (!status->isOk)
  {
    kod_memory_dealloc(mem, fn);
    return NULL;
  }
  return fn;
}

void kod_function_dealloc(KodFunction *fn, KodMemory *mem)
{
  kod_function_deinit(fn, mem);
  kod_memory_dealloc(mem, fn);
}

void kod_function_release(KodFunction *fn, KodMemory *mem)
{
  KodObject *obj = &fn->obj;
  kod_dec_ref(obj);
  if (kod_ref_count(obj))
    return;
  kod_function_dealloc(fn, mem);
}

uint8_t kod_function_inplace_add_nonlocal(KodFunction *fn, bool isLocal, uint8_t localIndex,
  KodMemory *mem, KodStatus *status)
{
  int index = fn->nonlocals.count;
  if (index > UINT8_MAX)
  {
    kod_status_error(status, "too many non-locals in function");
    return 0;
  }
  KodNonlocal nonlocal = { isLocal, localIndex };
  kod_vector_inplace_add(&fn->nonlocals, nonlocal, mem, status);
  if (!status->isOk)
    return 0;
  return (uint8_t) index;
}

uint8_t kod_function_inplace_add_child(KodFunction *fn, KodFunction *child,
  KodMemory *mem, KodStatus *status)
{
  int index = fn->functions.count;
  if (index > UINT8_MAX)
  {
    kod_status_error(status, "too many child functions in function");
    return 0;
  }
  kod_vector_inplace_add(&fn->functions, child, mem, status);
  if (!status->isOk)
    return 0;
  kod_inc_ref(&child->obj);
  return (uint8_t) index;
}
