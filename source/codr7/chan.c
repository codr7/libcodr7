#include "codr7/chan.h"
#include "codr7/error.h"

void c7_chan_init(struct c7_chan *chan, struct c7_dqpool *pool) {
  c7_deque_init(&chan->queue, pool);
  int result = thrd_error;

  if ((result = mtx_init(&chan->mutex, mtx_timed)) != thrd_success) {
    c7_error("Failed initializing chan mutex: %d", result);
  }

  if ((result = cnd_init(&chan->cond)) != thrd_success) {
    c7_error("Failed initializing chan cond: %d", result);
  }
}

void c7_chan_deinit(struct c7_chan *chan) {
  cnd_destroy(&chan->cond);
  mtx_destroy(&chan->mutex);
  c7_deque_clear(&chan->queue);
}

void *c7_chan_get_lock(struct c7_chan *chan) {
  int result = thrd_error;
  
  if ((result = cnd_wait(&chan->cond, &chan->mutex)) != thrd_success) {
    c7_error("Failed waiting on chan cond: %d", result);
  }

  return c7_deque_front(&chan->queue);
}

void c7_chan_get_unlock(struct c7_chan *chan) {
  int result = thrd_error;
  
  if ((result = mtx_unlock(&chan->mutex)) != thrd_success) {
    c7_error("Failed unlocking chan mutex: %d", result);
  }
}

void *c7_chan_put_lock(struct c7_chan *chan) {
  int result = thrd_error;

  if ((result = mtx_lock(&chan->mutex)) != thrd_success) {
    c7_error("Failed locking chan mutex: %d", result);
  }

  return c7_deque_push_back(&chan->queue);
}

void c7_chan_put_unlock(struct c7_chan *chan) {
  int result = thrd_error;

  if ((result = mtx_unlock(&chan->mutex)) != thrd_success) {
    c7_error("Failed unlocking chan mutex: %d", result);
  }

  if ((result = cnd_signal(&chan->cond)) != thrd_success) {
    c7_error("Failed signalling chan cond: %d", result);
  }
}
