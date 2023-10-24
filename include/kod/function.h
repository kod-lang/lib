//
// function.h
//

#ifndef KOD_FUNCTION_H
#define KOD_FUNCTION_H

#include "chunk.h"

typedef struct
{
  bool isLocal;
  uint8_t index;
} KodNonlocal;

typedef struct KodFunction
{
  KodObject obj;
  uint8_t arity;
  KodString *name;
  KodString *file;
  KodChunk chunk;
  KodVector(KodNonlocal) nonlocals;
  KodVector(struct KodFunction *) functions;
} KodFunction;

KOD_API void kod_function_init(KodFunction *fn, uint8_t arity, KodString *name, KodString *file,
  KodMemory *mem, KodStatus *status);
KOD_API void kod_function_deinit(KodFunction *fn, KodMemory *mem);
KOD_API KodFunction *kod_function_new(uint8_t arity, KodString *name, KodString *file,
  KodMemory *mem, KodStatus *status);
KOD_API void kod_function_dealloc(KodFunction *fn, KodMemory *mem);
KOD_API void kod_function_release(KodFunction *fn, KodMemory *mem);
KOD_API uint8_t kod_function_inplace_add_nonlocal(KodFunction *fn, bool isLocal, uint8_t localIndex,
  KodMemory *mem, KodStatus *status);
KOD_API uint8_t kod_function_inplace_add_child(KodFunction *fn, KodFunction *child,
  KodMemory *mem, KodStatus *status);

#endif // KOD_FUNCTION_H
