//
// value_test.c
//

#include <assert.h>
#include <stdlib.h>
#include "kod/value.h"

static inline void dummy_test(void);

static inline void dummy_test(void)
{
  assert(1);
}

int main(void)
{
  dummy_test();
  return EXIT_SUCCESS;
}
