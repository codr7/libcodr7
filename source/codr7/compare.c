#include <string.h>
#include "codr7/compare.h"

enum c7_order c7_compare_int(const void *x, const void *y) {
  int xi = *(const int *)x, yi = *(const int *)y;
  return (xi < yi) ? C7_LT : ((xi > yi) ? C7_GT : C7_EQ);
}

enum c7_order c7_compare_str(const void *x, const void *y) {
  int v = strcmp(x, y);

  if (v < 0) {
    return C7_LT;
  }
  
  return (v > 0) ? C7_GT : C7_EQ;
}
