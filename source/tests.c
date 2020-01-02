#include <assert.h>
#include <stdio.h>
#include "codr7/chan.h"
#include "codr7/deque.h"
#include "codr7/dqpool.h"
#include "codr7/rbnode.h"
#include "codr7/rbpool.h"
#include "codr7/rbtree.h"

static void deque_tests() {
  const int SLAB_SIZE = 32, N = 1024;

  struct c7_dqpool pool;
  c7_dqpool_init(&pool, SLAB_SIZE, sizeof(int));
  
  struct c7_deque deque;
  c7_deque_init(&deque, &pool);

  // Push first half in reverse to front
  for (int i = 0; i < N / 2; i++) {
    *(int *)c7_deque_push_front(&deque) = N / 2 - i - 1;
  }

  // Push second half to back
  for (int i = N / 2; i < N; i++) {
    *(int *)c7_deque_push_back(&deque) = i;
  }

  assert(deque.count == N);
  
  // Random access
  for (int i = 0; i < N; i++) {
    assert(*(int *)c7_deque_get(&deque, i) == i);
  }

  // Pop first quarter from front
  for (int i = 0; i < N / 4; i++) {
    assert(*(int *)c7_deque_front(&deque) == i);
    c7_deque_pop_front(&deque);
  }

  // Pop last quarter from back
  for (int i = 0; i < N / 4; i++) {
    assert(*(int *)c7_deque_back(&deque) == N - i - 1);
    c7_deque_pop_back(&deque);
  }

  assert(deque.count == N / 2);

  // Loop remaining
  int i = N / 4;

  c7_deque_do(&deque, p) {
    assert(*(int *)p == i++); 
  }

  // Clear
  c7_deque_clear(&deque);
  assert(!deque.count);
  
  c7_dqpool_deinit(&pool);
}

static bool fn(void *value, void *expected) {
  assert(*(int *)value == (*(int *)expected)++);
  return true;
}

static void rbtree_tests() {
  const int SLAB_SIZE = 32, N = 10;

  struct c7_rbpool pool;
  c7_rbpool_init(&pool, SLAB_SIZE, sizeof(int));
  
  struct c7_rbtree tree;
  c7_rbtree_init(&tree, c7_compare_int, &pool);
  int items[] = {9, 1, 2, 3, 5, 4, 6, 7, 8, 0};

  // Add items
  for (int i = 0; i < N; i++) {
    *(int *)c7_rbtree_add(&tree, items + i) = items[i];
  }

  // Try adding duplicates
  for (int i = 0; i < N; i++) {
    assert(!c7_rbtree_add(&tree, items + i));
  }

  assert(tree.count == N);

  // Find items
  for (int i = 0; i < N; i++) {
    assert(*(int *)c7_rbtree_find(&tree, items + i) == items[i]);
  }

  // Loop
  int i = 0;
  assert(c7_rbtree_while(&tree, fn, &i));
  assert(i == N);

  // Remove first half
  for (int i = 0; i < N / 2; i++) {
    assert(*(int *)c7_rbtree_remove(&tree, items + i) == items[i]);
  }

  assert(tree.count == N / 2);

  // Find remaining items
  for (int i = N / 2; i < N; i++) {
    assert(*(int *)c7_rbtree_find(&tree, items + i) == items[i]);
  }

  // Clear
  c7_rbtree_clear(&tree);
  assert(!tree.count);
  
  c7_rbpool_deinit(&pool);
}

void chan_tests() {
  const int SLAB_SIZE = 32;
  struct c7_dqpool pool;
  c7_dqpool_init(&pool, SLAB_SIZE, sizeof(int));
  struct c7_chan chan;
  c7_chan_init(&chan, &pool);
  c7_dqpool_deinit(&pool);
}

int main() {
  deque_tests();
  rbtree_tests();
  chan_tests();
  return 0;
}
