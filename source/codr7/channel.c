#include "codr7/channel.h"
#include "codr7/error.h"

void c7_channel_init(struct c7_channel *chan, struct c7_dqpool *pool) {
  c7_deque_init(&chan->queue, pool);
  int result = 0;

  if ((result = mtx_init(&chan->mutex, mtx_timed)) != thrd_success) {
    c7_error("Failed initializing channel mutex: %d", result);
  }

  if ((result = cnd_init(&chan->cond)) != thrd_success) {
    c7_error("Failed initializing channel cond: %d", result);
  }
}

void c7_channel_deinit(struct c7_channel *chan) {
  cnd_destroy(&chan->cond);
  mtx_destroy(&chan->mutex);
  c7_deque_clear(&chan->queue);
}
