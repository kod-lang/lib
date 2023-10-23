//
// utils_test.c
//

#include <assert.h>
#include <stdlib.h>
#include "kod/utils.h"

static inline void power_of_two_ceil_test(void);

static inline void power_of_two_ceil_test(void)
{
  assert(!kod_power_of_two_ceil(0));
  assert(kod_power_of_two_ceil(1) == 1);
  assert(kod_power_of_two_ceil(2) == 2);
  assert(kod_power_of_two_ceil(3) == 4);
  assert(kod_power_of_two_ceil(4) == 4);
  assert(kod_power_of_two_ceil(5) == 8);
  assert(kod_power_of_two_ceil(6) == 8);
  assert(kod_power_of_two_ceil(7) == 8);
  assert(kod_power_of_two_ceil(8) == 8);
}

int main(void)
{
  power_of_two_ceil_test();
  return EXIT_SUCCESS;
}
