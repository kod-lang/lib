//
// utils_test.c
//

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "../src/utils.h"

static inline void power_of_two_ceil_test(void);

static inline void power_of_two_ceil_test(void)
{
  assert(!power_of_two_ceil(0));
  assert(power_of_two_ceil(1) == 1);
  assert(power_of_two_ceil(2) == 2);
  assert(power_of_two_ceil(3) == 4);
  assert(power_of_two_ceil(4) == 4);
  assert(power_of_two_ceil(5) == 8);
  assert(power_of_two_ceil(6) == 8);
  assert(power_of_two_ceil(7) == 8);
  assert(power_of_two_ceil(8) == 8);
}

int main(void)
{
  power_of_two_ceil_test();
  return EXIT_SUCCESS;
}
