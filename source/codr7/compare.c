#include <stdint.h>
#include <string.h>

#include "codr7/compare.h"

enum c7_order c7_compare_int(const void *x, const void *y) {
  return C7_COMPARE(*(const int *)x, *(const int *)y);
}

enum c7_order c7_compare_int64(const void *x, const void *y) {
  return C7_COMPARE(*(const int64_t *)x, *(const int64_t *)y);
}

enum c7_order c7_compare_ptr(const void *x, const void *y) {
  return C7_COMPARE(x, y);
}

enum c7_order c7_compare_str(const void *x, const void *y) {
  int v = strcmp(x, y);
  return (v < 0) ? C7_LT : ((v > 0) ? C7_GT : C7_EQ);
}
