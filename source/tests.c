#include <assert.h>
#include <stdio.h>
#include "c7/rbpool.h"
#include "c7/rbtree.h"

static bool fn(void *value, void *expected) {
  assert(*(int *)value == (*(int *)expected)++);
  return true;
}

static void rbtree_tests() {
  struct c7_rbpool pool;
  c7_rbpool_init(&pool, 32, sizeof(int));
  
  struct c7_rbtree tree;
  c7_rbtree_init(&tree, c7_compare_int, &pool);
  const int N = 10;
  int items[] = {9, 1, 2, 3, 5, 4, 6, 7, 8, 0};

  // Insert items
  for (int i = 0; i < N; i++) {
    *(int *)c7_rbtree_add(&tree, items + i) = items[i];
  }

  // Find items
  for (int i = 0; i < N; i++) {
    assert(*(int *)c7_rbtree_find(&tree, items + i) == items[i]);
  }

  // Loop
  int i = 0;
  assert(c7_rbtree_while(&tree, fn, &i));
  assert(i == N);
  
  c7_rbtree_deinit(&tree);
  c7_rbpool_deinit(&pool);
}

int main() {
  rbtree_tests();
  return 0;
}
