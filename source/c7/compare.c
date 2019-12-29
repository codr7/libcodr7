#include "c7/compare.h"

enum c7_order c7_compare_int(const void *key, const void *value) {
  int k = *(const int *)key, v = *(const int *)value;
  return (k < v) ? C7_LT : ((k > v) ? C7_GT : C7_EQ);
}
