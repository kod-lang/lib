//
// status.c
//

#include "kod/status.h"
#include <stdarg.h>
#include <stdio.h>

void kod_status_error(KodStatus *status, const char *fmt, ...)
{
  status->isOk = false;
  va_list args;
  va_start(args, fmt);
  vsnprintf(status->error, sizeof(status->error), fmt, args);
  va_end(args);
}
