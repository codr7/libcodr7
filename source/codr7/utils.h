#ifndef C7_UTILS_H
#define C7_UTILS_H

#include <stddef.h>

#define c7_align(base, _size) ({					\
      __auto_type size = c7_min((_size), _Alignof(max_align_t));	\
      (base) + size - ((ptrdiff_t)(base)) % size;			\
    })									\

#define c7_baseof(p, t, m)			\
  ((t *)((char *)(p) - offsetof(t, m)))

#define _c7_id(x, y)				\
  x##y

#define c7_id(x, y)				\
  _c7_id(x, y)

#define c7_max(_x, _y) ({			\
      __auto_type x = (_x);			\
      __auto_type y = (_y);			\
      x > y ? x : y;				\
    })						\

#define c7_min(_x, _y) ({			\
      __auto_type x = (_x);			\
      __auto_type y = (_y);			\
      x < y ? x : y;				\
    })						\

#define c7_unique(x)				\
  c7_id(x, __COUNTER__)

char *c7_strdup(const char *in);

#endif
