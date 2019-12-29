#ifndef C7_COMPARE_H
#define C7_COMPARE_H

#include <stdbool.h>

enum c7_order {C7_LT, C7_EQ, C7_GT};

typedef enum c7_order (*c7_compare_t)(const void *key, const void *value);

enum c7_order c7_compare_int(const void *key, const void *value);

typedef bool (*c7_predicate_t)(void *value, void *arg);

#endif
