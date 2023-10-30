//
// chunk.h
//

#ifndef KOD_CHUNK_H
#define KOD_CHUNK_H

#include "string.h"
#include "vector.h"

#define kod_instr0(op)          ((uint32_t) (op))
#define kod_instr1(op, a)       ((((uint32_t) (a)) << 8) | (op))
#define kod_instr2(op, a, b)    ((((((uint32_t) (b)) << 8) | (a)) << 8) | (op))
#define kod_instr3(op, a, b, c) (((((((uint32_t) (c)) << 8) | (b)) << 8) | (a)) << 8) | (op)

#define kod_instr_op(instr) ((instr) & 0xff)
#define kod_instr_a(instr)  (((instr) >> 8) & 0xff)
#define kod_instr_b(instr)  (((instr) >> 16) & 0xff)
#define kod_instr_c(instr)  (((instr) >> 24) & 0xff)
#define kod_instr_ab(instr) (((instr) >> 8) & 0xffff)
#define kod_instr_bc(instr) (((instr) >> 16) & 0xffff)

#define kod_instr_null(r0)                   (kod_instr1(KOD_OP_NULL, (r0)))
#define kod_instr_false(r0)                  (kod_instr1(KOD_OP_FALSE, (r0)))
#define kod_instr_true(r0)                   (kod_instr1(KOD_OP_TRUE, (r0)))
#define kod_instr_int(imm)                   (kod_instr1(KOD_OP_INT, (imm)))
#define kod_instr_number(idx)                (kod_instr1(KOD_OP_NUMBER, (idx)))
#define kod_instr_string(idx)                (kod_instr1(KOD_OP_STRING, (idx)))
#define kod_instr_closure(r0, idx)           (kod_instr2(KOD_OP_CLOSURE, (r0), (idx)))
#define kod_instr_reference(r0, idx)         (kod_instr2(KOD_OP_REFERENCE, (r0), (idx)))
#define kod_instr_move(r0, r1)               (kod_instr2(KOD_OP_MOVE, (r0), (r1)))
#define kod_instr_move_from_ref(r0, r1)      (kod_instr2(KOD_OP_MOVE_FROM_REF, (r0), (r1)))
#define kod_instr_move_to_ref(r0, r1)        (kod_instr2(KOD_OP_MOVE_TO_REF, (r0), (r1)))
#define kod_instr_get_nonlocal(r0, idx)      (kod_instr2(KOD_OP_GET_NONLOCAL, (r0), (idx)))
#define kod_instr_set_nonlocal(r0, idx)      (kod_instr2(KOD_OP_SET_NONLOCAL, (r0), (idx)))
#define kod_instr_range(r0, r1, r2)          (kod_instr3(KOD_OP_RANGE, (r0), (r1), (r2)))
#define kod_instr_add(r0, r1, r2)            (kod_instr3(KOD_OP_ADD, (r0), (r1), (r2)))
#define kod_instr_add_int(r0, r1, imm)       (kod_instr3(KOD_OP_ADD_INT, (r0), (r1), (imm)))
#define kod_instr_subtract(r0, r1, r2)       (kod_instr3(KOD_OP_SUBTRACT, (r0), (r1), (r2)))
#define kod_instr_subtract_int(r0, r1, imm)  (kod_instr3(KOD_OP_SUBTRACT_INT, (r0), (r1), (imm)))
#define kod_instr_int_subtract(r0, r1, imm)  (kod_instr3(KOD_OP_INT_SUBTRACT, (r0), (r1), (imm)))
#define kod_instr_multiply(r0, r1, r2)       (kod_instr3(KOD_OP_MULTIPLY, (r0), (r1), (r2)))
#define kod_instr_multiply_int(r0, r1, imm)  (kod_instr3(KOD_OP_MULTIPLY_INT, (r0), (r1), (imm)))
#define kod_instr_divide(r0, r1, r2)         (kod_instr3(KOD_OP_DIVIDE, (r0), (r1), (r2)))
#define kod_instr_divide_int(r0, r1, imm)    (kod_instr3(KOD_OP_DIVIDE_INT, (r0), (r1), (imm)))
#define kod_instr_int_divide(r0, r1, imm)    (kod_instr3(KOD_OP_INT_DIVIDE, (r0), (r1), (imm)))
#define kod_instr_remainder(r0, r1, r2)      (kod_instr3(KOD_OP_REMAINDER, (r0), (r1), (r2)))
#define kod_instr_remainder_int(r0, r1, imm) (kod_instr3(KOD_OP_REMAINDER_INT, (r0), (r1), (imm)))
#define kod_instr_int_remainder(r0, r1, imm) (kod_instr3(KOD_OP_INT_REMAINDER, (r0), (r1), (imm)))
#define kod_instr_negate(r0, r1)             (kod_instr2(KOD_OP_NEGATE, (r0), (r1)))
#define kod_instr_not(r0, r1)                (kod_instr2(KOD_OP_NOT, (r0), (r1)))
#define kod_instr_equal(r0, r1, r2)          (kod_instr3(KOD_OP_EQUAL, (r0), (r1), (r2)))
#define kod_instr_not_equal(r0, r1, r2)      (kod_instr3(KOD_OP_NOT_EQUAL, (r0), (r1), (r2)))
#define kod_instr_less(r0, r1, r2)           (kod_instr3(KOD_OP_LESS, (r0), (r1), (r2)))
#define kod_instr_not_less(r0, r1, r2)       (kod_instr3(KOD_OP_NOT_LESS, (r0), (r1), (r2)))
#define kod_instr_greater(r0, r1, r2)        (kod_instr3(KOD_OP_GREATER, (r0), (r1), (r2)))
#define kod_instr_not_greater(r0, r1, r2)    (kod_instr3(KOD_OP_NOT_GREATER, (r0), (r1), (r2)))
#define kod_instr_jump(off)                  (kod_instr1(KOD_OP_JUMP, (off)))
#define kod_instr_jump_if_false(r0, off)     (kod_instr2(KOD_OP_JUMP_IF_FALSE, (r0), (off)))
#define kod_instr_jump_if_true(r0, off)      (kod_instr2(KOD_OP_JUMP_IF_TRUE, (r0), (off)))
#define kod_instr_loop(off)                  (kod_instr1(KOD_OP_LOOP, (off)))
#define kod_instr_call(r0, r1, n)            (kod_instr3(KOD_OP_CALL, (r0), (r1), (n)))
#define kod_instr_tail_call(r0, r1, n)       (kod_instr3(KOD_OP_TAIL_CALL, (r0), (r1), (n)))
#define KOD_INSTR_RETURN                     (kod_instr0(KOD_OP_RETURN))

#define kod_chunk_inplace_emit(c, instr, m, s) \
  do { \
    kod_vector_inplace_add(&(c)->instructions, (instr), (m), (s)); \
  } while (0)

typedef enum
{
  KOD_OP_NULL,          // Null         <r0>
  KOD_OP_FALSE,         // False        <r0>
  KOD_OP_TRUE,          // True         <r0>
  KOD_OP_INT,           // Int          <r0>  <imm>
  KOD_OP_NUMBER,        // Number       <r0>  <idx>
  KOD_OP_STRING,        // String       <r0>  <idx>
  KOD_OP_CLOSURE,       // Closure      <r0>  <idx>
  KOD_OP_REFERENCE,     // Reference    <r0>  <idx>
  KOD_OP_MOVE,          // Move         <r0>  <r1>
  KOD_OP_MOVE_FROM_REF, // MoveFromRef  <r0>  <r1>
  KOD_OP_MOVE_TO_REF,   // MoveToRef    <r0>  <r1>
  KOD_OP_GET_NONLOCAL,  // GetNonLocal  <r0>  <idx>
  KOD_OP_SET_NONLOCAL,  // SetNonLocal  <r0>  <idx>
  KOD_OP_RANGE,         // Range        <r0>  <r1>  <r2>
  KOD_OP_ADD,           // Add          <r0>  <r1>  <r2>
  KOD_OP_ADD_INT,       // AddInt       <r0>  <r1>  <imm>
  KOD_OP_SUBTRACT,      // Subtract     <r0>  <r1>  <r2>
  KOD_OP_SUBTRACT_INT,  // SubtractInt  <r0>  <r1>  <imm>
  KOD_OP_INT_SUBTRACT,  // IntSubtract  <r0>  <r1>  <imm>
  KOD_OP_MULTIPLY,      // Multiply     <r0>  <r1>  <r2>
  KOD_OP_MULTIPLY_INT,  // MultiplyInt  <r0>  <r1>  <imm>
  KOD_OP_DIVIDE,        // Divide       <r0>  <r1>  <r2>
  KOD_OP_DIVIDE_INT,    // DivideInt    <r0>  <r1>  <imm>
  KOD_OP_INT_DIVIDE,    // IntDivide    <r0>  <r1>  <imm>
  KOD_OP_REMAINDER,     // Remainder    <r0>  <r1>  <r2>
  KOD_OP_REMAINDER_INT, // RemainderInt <r0>  <r1>  <imm>
  KOD_OP_INT_REMAINDER, // IntRemainder <r0>  <r1>  <imm>
  KOD_OP_NEGATE,        // Negate       <r0>  <r1>
  KOD_OP_NOT,           // Not          <r0>  <r1>
  KOD_OP_EQUAL,         // Equal        <r0>  <r1>  <r2>
  KOD_OP_NOT_EQUAL,     // NotEqual     <r0>  <r1>  <r2>
  KOD_OP_LESS,          // Less         <r0>  <r1>  <r2>
  KOD_OP_NOT_LESS,      // NotLess      <r0>  <r1>  <r2>
  KOD_OP_GREATER,       // Greater      <r0>  <r1>  <r2>
  KOD_OP_NOT_GREATER,   // NotGreater   <r0>  <r1>  <r2>
  KOD_OP_JUMP,          // Jump         <off>
  KOD_OP_JUMP_IF_FALSE, // JumpIfFalse  <r0>  <off>
  KOD_OP_JUMP_IF_TRUE,  // JumpIfTrue   <r0>  <off>
  KOD_OP_LOOP,          // Loop         <off>
  KOD_OP_CALL,          // Call         <r0>  <r1>  <n>
  KOD_OP_TAIL_CALL,     // TailCall     <r0>  <r1>  <n>
  KOD_OP_RETURN         // Return
} KodOpcode;

typedef struct
{
  KodVector(uint32_t) instructions;
  KodVector(double) numbers;
  KodVector(KodString *) strings;
} KodChunk;

KOD_API void kod_chunk_init(KodChunk *chunk, KodMemory *mem, KodStatus *status);
KOD_API void kod_chunk_deinit(KodChunk *chunk, KodMemory *mem);
KOD_API uint8_t kod_chunk_inplace_add_number(KodChunk *chunk, double num, KodMemory *mem, KodStatus *status);
KOD_API uint8_t kod_chunk_inplace_add_string(KodChunk *chunk, KodString *str, KodMemory *mem, KodStatus *status);

#endif // KOD_CHUNK_H
