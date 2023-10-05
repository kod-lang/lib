//
// status.h
//

#ifndef KOD_STATUS_H
#define KOD_STATUS_H

#include <stdbool.h>
#include "common.h"

#define KOD_STATUS_ERROR_MAX_LENGTH (255)

#define kod_status_ok(s) \
  do { \
    (s)->isOk = true; \
  } while (0)

typedef struct
{
  bool isOk;
  char error[KOD_STATUS_ERROR_MAX_LENGTH + 1];
} KodStatus;

KOD_API void kod_status_error(KodStatus *status, const char *fmt, ...);

#endif // KOD_STATUS_H
