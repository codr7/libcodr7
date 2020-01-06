#ifndef C7_UTILS_H
#define C7_UTILS_H

#include <stddef.h>

#define c7_align(base, size) ({						\
      __auto_type _base = base;						\
      __auto_type _size = c7_min((size), _Alignof(max_align_t));	\
      (_base) + _size - ((ptrdiff_t)(_base)) % _size;			\
    })									\

#define c7_baseof(p, t, m) ({			\
      uint8_t *_p = (uint8_t *)p;		\
      _p ? ((t *)(_p - offsetof(t, m))) : NULL;	\
    })

#define _c7_id(x, y)				\
  x##y

#define c7_id(x, y)				\
  _c7_id(x, y)

#define c7_max(x, y) ({				\
      __auto_type _x = x;			\
      __auto_type _y = y;			\
      _x > _y ? _x : _y;			\
    })						\

#define c7_min(x, y) ({				\
      __auto_type _x = x;			\
      __auto_type _y = y;			\
      _x < _y ? _x : _y;			\
    })						\

#define c7_unique(x)				\
  c7_id(x, __COUNTER__)

char *c7_strdup(const char *in);

#endif
