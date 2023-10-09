//
// value.h
//

#ifndef KOD_VALUE_H
#define KOD_VALUE_H

#include <stdint.h>
#include "memory.h"

#define KOD_FLAG_NONE   0x00
#define KOD_FLAG_FALSY  0x01
#define KOD_FLAG_OBJECT 0x02

#define KOD_NULL_VALUE      ((KodValue) { .type = KOD_TYPE_NULL, .flags = KOD_FLAG_FALSY })
#define KOD_FALSE_VALUE     ((KodValue) { .type = KOD_TYPE_BOOLEAN, .flags = KOD_FLAG_FALSY, .asBoolean = false })
#define KOD_TRUE_VALUE      ((KodValue) { .type = KOD_TYPE_BOOLEAN, .flags = KOD_FLAG_NONE, .asBoolean = true })
#define kod_number_value(n) ((KodValue) { .type = KOD_TYPE_NUMBER, .flags = KOD_FLAG_NONE, .asNumber = (n) })
#define kod_rune_value(r)   ((KodValue) { .type = KOD_TYPE_RUNE, .flags = KOD_FLAG_NONE, .asRune = (r) })
#define kod_string_value(s) ((KodValue) { .type = KOD_TYPE_STRING, .flags = KOD_FLAG_OBJECT, .asPointer = (s) })

#define kod_type(v)  ((v).type)
#define kod_flags(v) ((v).flags)

#define kod_is_null(v)    (kod_type(v) == KOD_TYPE_NULL)
#define kod_is_boolean(v) (kod_type(v) == KOD_TYPE_BOOLEAN)
#define kod_is_number(v)  (kod_type(v) == KOD_TYPE_NUMBER)
#define kod_is_rune(v)    (kod_type(v) == KOD_TYPE_RUNE)
#define kod_is_string(v)  (kod_type(v) == KOD_TYPE_STRING)
#define kod_is_falsy(v)   (kod_flags(v) & KOD_FLAG_FALSY)
#define kod_is_object(v)  (kod_flags(v) & KOD_FLAG_OBJECT)

#define kod_as_boolean(v) ((v).asBoolean)
#define kod_as_number(v)  ((v).asNumber)
#define kod_as_rune(v)    ((v).asRune)
#define kod_as_string(v)  ((KodString *) (v).asPointer)
#define kod_as_object(v)  ((KodObject *) (v).asPointer)

#define kod_object_init(o) \
  do { \
    (o)->refCount = 0; \
  } while (0)

#define kod_ref_count(o) ((o)->refCount)

#define kod_inc_ref(o) \
  do { \
    ++(o)->refCount; \
  } while (0)

#define kod_dec_ref(o) \
  do { \
    --(o)->refCount; \
  } while (0)

#define kod_value_retain(v) \
  do { \
    if (kod_is_object(v)) { \
      ++kod_as_object(v)->refCount; \
    } \
  } while (0)

typedef enum
{
  KOD_TYPE_NULL,
  KOD_TYPE_BOOLEAN,
  KOD_TYPE_NUMBER,
  KOD_TYPE_RUNE,
  KOD_TYPE_STRING
} KodType;

typedef struct
{
  KodType type;
  int flags;
  union
  {
    bool asBoolean;
    double asNumber;
    uint32_t asRune;
    void *asPointer;
  };
} KodValue;

typedef struct
{
  int refCount;
} KodObject;

KOD_API const char *kod_type_name(KodType type);
KOD_API void kod_value_free(KodValue val, KodMemory *mem);
KOD_API void kod_value_release(KodValue val, KodMemory *mem);

#endif // KOD_VALUE_H
