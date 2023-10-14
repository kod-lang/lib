//
// chunk.c
//

#include "kod/chunk.h"

void kod_chunk_init(KodChunk *chunk, KodMemory *mem, KodStatus *status)
{
  kod_vector_init(&chunk->instructions, mem, status);
  if (!status->isOk)
    return;
  kod_vector_init(&chunk->numbers, mem, status);
  if (!status->isOk)
    return;
  kod_vector_init(&chunk->strings, mem, status);
  if (!status->isOk)
    return;
}

void kod_chunk_deinit(KodChunk *chunk, KodMemory *mem)
{
  kod_vector_deinit(&chunk->instructions, mem);
  kod_vector_deinit(&chunk->numbers, mem);
  for (int i = 0; i < chunk->strings.count; ++i)
  {
    KodString *str = kod_vector_get(&chunk->strings, i);
    kod_string_release(str, mem);
  }
  kod_vector_deinit(&chunk->strings, mem);
}
