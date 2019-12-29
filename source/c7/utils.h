#ifndef C7_UTILS_H
#define C7_UTILS_H

#include <stddef.h>

#define c7_baseof(p, t, m)			\
  ((t *)((char *)(p) - offsetof(t, m)))

#define _c7_id(x, y)				\
  x##y

#define c7_id(x, y)				\
  _c7_id(x, y)

#define c7_unique(x)				\
  c7_id(x, __COUNTER__)

#endif
