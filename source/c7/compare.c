#include <string.h>
#include "c7/compare.h"

enum c7_order c7_compare_int(const void *x, const void *y) {
  int xi = *(const int *)x, yi = *(const int *)y;
  return (xi < yi) ? C7_LT : ((xi > yi) ? C7_GT : C7_EQ);
}

enum c7_order c7_compare_str(const void *x, const void *y) {
  switch(strcmp(x, y)) {
  case -1:
    return C7_LT;
  case 1:
    return C7_GT;
  default:
    break;
  }

  return C7_EQ;
}
