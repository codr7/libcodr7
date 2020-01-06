#ifndef C7_COMPARE_H
#define C7_COMPARE_H

#include <stdbool.h>

#define C7_COMPARE(x, y) ({				\
      __auto_type _x = x;				\
      __auto_type _y = y;				\
      (_x < _y) ? C7_LT : ((_x > _y) ? C7_GT : C7_EQ);	\
    })

enum c7_order {C7_LT, C7_EQ, C7_GT};

typedef enum c7_order (*c7_compare_t)(const void *key, const void *value);

enum c7_order c7_compare_int(const void *x, const void *y);
enum c7_order c7_compare_int64(const void *x, const void *y);
enum c7_order c7_compare_ptr(const void *x, const void *y);
enum c7_order c7_compare_str(const void *x, const void *y);

#endif
