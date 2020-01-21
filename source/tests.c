#include <assert.h>
#include <stdio.h>

#include "codr7/chan.h"
#include "codr7/deque.h"
#include "codr7/deque_pool.h"
#include "codr7/tree.h"
#include "codr7/tree_node.h"
#include "codr7/tree_pool.h"

static void deque_tests() {
  const int SLAB_SIZE = 32, N = 1024;

  struct c7_deque_pool pool;
  c7_deque_pool_init(&pool, SLAB_SIZE, sizeof(int));
  
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
  
  c7_deque_pool_deinit(&pool);
}

static enum c7_order compare_int(const void *x, const void *y) {
  return c7_compare(*(int *)x, *(int *)y);
}

static void tree_tests() {
  const int SLAB_SIZE = 32, N = 10;

  struct c7_tree_pool pool;
  c7_tree_pool_init(&pool, SLAB_SIZE, sizeof(int));
  
  struct c7_tree tree;
  c7_tree_init(&tree, compare_int, &pool);
  int items[] = {9, 1, 2, 3, 5, 4, 6, 7, 8, 0};

  // Add items
  for (int i = 0; i < N; i++) {
    *(int *)c7_tree_add(&tree, items + i) = items[i];
  }

  // Try adding duplicates
  for (int i = 0; i < N; i++) {
    assert(!c7_tree_add(&tree, items + i));
  }

  assert(tree.count == N);

  // Find items
  for (int i = 0; i < N; i++) {
    assert(*(int *)c7_tree_find(&tree, items + i) == items[i]);
  }

  // Loop
  int i = 0;

  c7_tree_do(&tree, p) {
    assert(*(int *)p == i++);
  }

  assert(i == N);

  // Remove first half
  for (int i = 0; i < N / 2; i++) {
    assert(*(int *)c7_tree_remove(&tree, items + i) == items[i]);
  }

  assert(tree.count == N / 2);

  // Find remaining items
  for (int i = N / 2; i < N; i++) {
    assert(*(int *)c7_tree_find(&tree, items + i) == items[i]);
  }

  // Clear
  c7_tree_clear(&tree);
  assert(!tree.count);
  
  c7_tree_pool_deinit(&pool);
}

static int chan_fn1(void *_chan) {
  struct c7_chan *chan = _chan;

  for (uint64_t i = 0; i < 100; i++) {
    *(uint64_t *)c7_chan_put_lock(chan, NULL) = i;
    c7_chan_put_unlock(chan);
  }
  
  return 42;
}
	    
static int chan_fn2(void *_chan) {
  struct c7_chan *chan = _chan;

  for (uint64_t i = 0; i < 100; i++) {
    assert(*(uint64_t *)c7_chan_get_lock(chan, NULL) == i);
    c7_chan_get_unlock(chan);
  }
  
  return 42;
}

void chan_tests() {
  const int QUEUE_MAX = 100;
  
  struct c7_chan chan;
  c7_chan_init(&chan, QUEUE_MAX, sizeof(uint64_t), QUEUE_MAX);

  thrd_t thread1, thread2;
  assert(thrd_create(&thread1, chan_fn1, &chan) == thrd_success);
  assert(thrd_create(&thread2, chan_fn2, &chan) == thrd_success);

  int ret = 0;
  assert(thrd_join(thread1, &ret) == thrd_success);
  assert(ret == 42);

  ret = 0;
  assert(thrd_join(thread2, &ret) == thrd_success);
  assert(ret == 42);

  c7_chan_deinit(&chan);
}

int main() {  
  deque_tests();
  tree_tests();
  chan_tests();
  return 0;
}
