//
// status_test.c
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "kod/status.h"

static inline void status_ok_test(void);
static inline void status_error_test(void);

static inline void status_ok_test(void)
{
  KodStatus status;
  kod_status_ok(&status);
  assert(status.isOk);
}

static inline void status_error_test(void)
{
  KodStatus status;
  kod_status_error(&status, "something went wrong");
  assert(!status.isOk);
  assert(!strcmp(status.error, "something went wrong"));
}

int main(void)
{
  status_ok_test();
  status_error_test();
  return EXIT_SUCCESS;
}
