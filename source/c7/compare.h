#ifndef C7_COMPARE_H
#define C7_COMPARE_H

enum c7_order {C7_LT, C7_EQ, C7_GT};

typedef enum c7_order (*c7_compare_t)(const void *key, const void *value);

enum c7_order c7_compare_int(const void *key, const void *value);

#endif
