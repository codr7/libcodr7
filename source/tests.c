#include <assert.h>
#include <stdio.h>
#include "c7/rbpool.h"
#include "c7/rbtree.h"

enum c7_order compare_int(const void *key, const void *value) {
  int k = *(const int *)key, v = *(const int *)value;
  return (k < v) ? C7_LT : ((k > v) ? C7_GT : C7_EQ);
}

int main() {
  struct c7_rbpool pool;
  c7_rbpool_init(&pool, 32, sizeof(int));
  
  struct c7_rbtree tree;
  c7_rbtree_init(&tree, compare_int, &pool);
  const int N = 3;
  int items[] = {2, 1, 3};

  for (int i = 0; i < N; i++) {
    *(int *)c7_rbtree_insert(&tree, items + i) = items[i];
  }
  
  c7_rbtree_deinit(&tree);
  c7_rbpool_deinit(&pool);
  return 0;
}
