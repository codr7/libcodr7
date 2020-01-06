#include <stdint.h>
#include <string.h>

#include "codr7/compare.h"

enum c7_order c7_strcmp(const char *x, const char *y) {
  int v = strcmp(x, y);
  return (v < 0) ? C7_LT : ((v > 0) ? C7_GT : C7_EQ);
}
