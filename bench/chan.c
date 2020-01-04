#include <assert.h>
#include <inttypes.h>
#include <stdio.h>

#include "codr7/chan.h"
#include "codr7/timer.h"

static int chan_fn1(void *_chan) {
  struct c7_chan *chan = _chan;

  for (uint64_t i = 0; i < 10000000; i++) {
    *(uint64_t *)c7_chan_put_lock(chan, NULL) = i;
    c7_chan_put_unlock(chan);
  }
  
  return 0;
}
	    
static int chan_fn2(void *_chan) {
  struct c7_chan *chan = _chan;

  for (uint64_t i = 0; i < 10000000; i++) {
    c7_chan_get_lock(chan, NULL);
    c7_chan_get_unlock(chan);
  }
  
  return 0;
}

int main() {
  const int QUEUE_MAX = 100;
  
  struct c7_chan chan;
  c7_chan_init(&chan, QUEUE_MAX, sizeof(uint64_t), QUEUE_MAX);

  struct c7_timer t;
  c7_timer_reset(&t);
  
  thrd_t thread1, thread2;
  assert(thrd_create(&thread1, chan_fn1, &chan) == thrd_success);
  assert(thrd_create(&thread2, chan_fn2, &chan) == thrd_success);

  int ret = 0;
  assert(thrd_join(thread1, &ret) == thrd_success);
  assert(thrd_join(thread2, &ret) == thrd_success);

  printf("chan: %" PRIu64 "us\n", c7_timer_usecs(&t));
  c7_chan_deinit(&chan);
  return 0;
}
