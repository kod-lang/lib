//
// chunk_test.c
//

#include <assert.h>
#include <stdlib.h>
#include "kod/chunk.h"

static void *memory_alloc(size_t size, void *udata);
static void *memory_realloc(void *ptr, size_t size, void *udata);
static void memory_dealloc(void *ptr, void *udata);

static KodMemory mem = {
  .alloc = memory_alloc,
  .realloc = memory_realloc,
  .dealloc = memory_dealloc,
  .udata = NULL
};

static inline void chunk_init_test(void);
static inline void chunk_inplace_emit_test(void);
static inline void chunk_inplace_add_number_test(void);
static inline void chunk_inplace_add_string_test(void);

static void *memory_alloc(size_t size, void *udata)
{
  (void) udata;
  return malloc(size);
}

static void *memory_realloc(void *ptr, size_t size, void *udata)
{
  (void) udata;
  return realloc(ptr, size);
}

static void memory_dealloc(void *ptr, void *udata)
{
  (void) udata;
  free(ptr);
}

static inline void chunk_init_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodChunk chunk;
  kod_chunk_init(&chunk, &mem, &status);
  assert(status.isOk);
  assert(chunk.instructions.capacity == KOD_VECTOR_MIN_CAPACITY);
  assert(!chunk.instructions.count);
  assert(chunk.instructions.elements);
  assert(chunk.numbers.capacity == KOD_VECTOR_MIN_CAPACITY);
  assert(!chunk.numbers.count);
  assert(chunk.numbers.elements);
  assert(chunk.strings.capacity == KOD_VECTOR_MIN_CAPACITY);
  assert(!chunk.strings.count);
  assert(chunk.strings.elements);
  kod_chunk_deinit(&chunk, &mem);
}

static inline void chunk_inplace_emit_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodChunk chunk;
  kod_chunk_init(&chunk, &mem, &status);
  assert(status.isOk);
  kod_chunk_inplace_emit(&chunk, KOD_INSTR_RETURN, &mem, &status);
  assert(status.isOk);
  assert(chunk.instructions.count == 1);
  assert(kod_vector_get(&chunk.instructions, 0) == KOD_INSTR_RETURN);
  kod_chunk_inplace_emit(&chunk, kod_instr_null(1), &mem, &status);
  assert(status.isOk);
  assert(chunk.instructions.count == 2);
  assert(kod_vector_get(&chunk.instructions, 1) == kod_instr_null(1));
  kod_chunk_inplace_emit(&chunk, kod_instr_closure(1, 2), &mem, &status);
  assert(status.isOk);
  assert(chunk.instructions.count == 3);
  assert(kod_vector_get(&chunk.instructions, 2) == kod_instr_closure(1, 2));
  kod_chunk_inplace_emit(&chunk, kod_instr_add(1, 2, 3), &mem, &status);
  assert(status.isOk);
  assert(chunk.instructions.count == 4);
  assert(kod_vector_get(&chunk.instructions, 3) == kod_instr_add(1, 2, 3));
  kod_chunk_deinit(&chunk, &mem);
}

static inline void chunk_inplace_add_number_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodChunk chunk;
  kod_chunk_init(&chunk, &mem, &status);
  assert(status.isOk);
  uint8_t index = kod_chunk_inplace_add_number(&chunk, (double) 1.23, &mem, &status);
  assert(status.isOk);
  assert(!index);
  assert(chunk.numbers.count == 1);
  assert(kod_vector_get(&chunk.numbers, 0) == (double) 1.23);
  kod_chunk_deinit(&chunk, &mem);
}

static inline void chunk_inplace_add_string_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  KodChunk chunk;
  kod_chunk_init(&chunk, &mem, &status);
  assert(status.isOk);
  KodString *str = kod_string_new_from("foo", &mem, &status);
  assert(status.isOk);
  uint8_t index = kod_chunk_inplace_add_string(&chunk, str, &mem, &status);
  assert(status.isOk);
  assert(!index);
  assert(chunk.strings.count == 1);
  assert(kod_vector_get(&chunk.strings, 0) == str);
  kod_chunk_deinit(&chunk, &mem);
}

int main(void)
{
  chunk_init_test();
  chunk_inplace_emit_test();
  chunk_inplace_add_number_test();
  chunk_inplace_add_string_test();
  return EXIT_SUCCESS;
}
