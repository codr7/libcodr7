#include <stdbool.h>

#include "codr7/chan.h"
#include "codr7/error.h"

void c7_chan_init(struct c7_chan *chan,
		  uint16_t slab_size,
		  uint16_t item_size,
		  uint64_t queue_max) {
  c7_dqpool_init(&chan->queue_pool, slab_size, item_size);
  c7_deque_init(&chan->queue, &chan->queue_pool);
  chan->queue_max = queue_max;
  int result = thrd_error;

  if ((result = mtx_init(&chan->mutex, mtx_timed)) != thrd_success) {
    c7_error("Failed initializing mutex: %d", result);
  }

  if ((result = cnd_init(&chan->put)) != thrd_success) {
    c7_error("Failed initializing put: %d", result);
  }

  if (queue_max && (result = cnd_init(&chan->get)) != thrd_success) {
    c7_error("Failed initializing get: %d", result);
  }
}

void c7_chan_deinit(struct c7_chan *chan) {
  if (chan->queue_max) {
    cnd_destroy(&chan->get);
  }
  
  cnd_destroy(&chan->put);
  mtx_destroy(&chan->mutex);
  c7_deque_clear(&chan->queue);
  c7_dqpool_deinit(&chan->queue_pool);
}

static bool lock(mtx_t *mutex, const struct timespec *deadline) {
  int result = thrd_error;

  if (deadline) {
    switch((result = mtx_timedlock(mutex, deadline))) {
    case thrd_success:
      break;
    case thrd_timedout:
      return false;
    default:
      c7_error("Failed locking mutex: %d", result);
    }
  } else if ((result = mtx_lock(mutex)) != thrd_success) {
    c7_error("Failed locking mutex: %d", result);
  }

  return true;
}

static bool wait(cnd_t *cond, mtx_t *mutex, const struct timespec *deadline) {
    int result = thrd_error;

    if (deadline) {
      switch ((result = cnd_timedwait(cond, mutex, deadline))) {
      case thrd_success:
	break;
      case thrd_timedout:
	if ((result = mtx_unlock(mutex)) != thrd_success) {
	  c7_error("Failed unlocking mutex: %d", result);
	}
	
	return false;
      default:
	c7_error("Failed waiting on cond: %d", result);
      }
    } else if ((result = cnd_wait(cond, mutex)) != thrd_success) {
      c7_error("Failed waiting on cond: %d", result);
    }

    return true;
}

void *c7_chan_put_lock(struct c7_chan *chan, const struct timespec *deadline) {
  if (!lock(&chan->mutex, deadline)) {
    return NULL;
  }

  while (chan->queue_max &&
	 chan->queue.count >= chan->queue_max) {
    if (!wait(&chan->get, &chan->mutex, deadline)) {
      return NULL;
    }
  }
  
  return c7_deque_push_back(&chan->queue);
}

void c7_chan_put_unlock(struct c7_chan *chan) {
  int result = thrd_error;

  if ((result = mtx_unlock(&chan->mutex)) != thrd_success) {
    c7_error("Failed unlocking mutex: %d", result);
  }

  if ((result = cnd_signal(&chan->put)) != thrd_success) {
    c7_error("Failed signalling put: %d", result);
  }
}

void *c7_chan_get_lock(struct c7_chan *chan, const struct timespec *deadline) {
  if (!lock(&chan->mutex, deadline)) {
    return NULL;
  }
  
  while (!chan->queue.count) {
    if (!wait(&chan->put, &chan->mutex, deadline)) {
      return NULL;
    }
  }

  return c7_deque_front(&chan->queue);
}

void c7_chan_get_unlock(struct c7_chan *chan) {
  c7_deque_pop_front(&chan->queue);
  bool signal_get = chan->queue.count < chan->queue_max;
  int result = thrd_error;

  if ((result = mtx_unlock(&chan->mutex)) != thrd_success) {
    c7_error("Failed unlocking mutex: %d", result);
  }

  if (signal_get && (result = cnd_signal(&chan->get)) != thrd_success) {
    c7_error("Failed signalling get: %d", result);
  }
}
