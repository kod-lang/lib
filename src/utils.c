//
// utils.c
//

#include "utils.h"

int power_of_two_ceil(int n)
{
  --n;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  ++n;  
  return n;
}
