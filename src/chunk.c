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
  {
    kod_vector_deinit(&chunk->instructions, mem);
    return;
  }
  kod_vector_init(&chunk->strings, mem, status);
  if (status->isOk)
    return;
  kod_vector_deinit(&chunk->instructions, mem);
  kod_vector_deinit(&chunk->numbers, mem);
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

uint8_t kod_chunk_inplace_add_number(KodChunk *chunk, double num, KodMemory *mem, KodStatus *status)
{
  int index = chunk->numbers.count;
  if (index > UINT8_MAX)
  {
    kod_status_error(status, "too many numbers in chunk");
    return 0;
  }
  kod_vector_inplace_add(&chunk->numbers, num, mem, status);
  if (!status->isOk)
    return 0;
  return (uint8_t) index;
}

uint8_t kod_chunk_inplace_add_string(KodChunk *chunk, KodString *str, KodMemory *mem, KodStatus *status)
{
  int index = chunk->strings.count;
  if (index > UINT8_MAX)
  {
    kod_status_error(status, "too many strings in chunk");
    return 0;
  }
  kod_vector_inplace_add(&chunk->strings, str, mem, status);
  if (!status->isOk)
    return 0;
  kod_inc_ref(&str->obj);
  return (uint8_t) index;
}
