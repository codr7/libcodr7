#include <errno.h>

#include "codr7/error.h"
#include "codr7/timer.h"

void c7_timer_reset(struct c7_timer *timer) {
  if (!timespec_get(&timer->start, TIME_UTC)) {
    c7_error("Failed getting time: %d", errno);
  }
}

uint64_t c7_timer_nsecs(const struct c7_timer *timer) {
  struct timespec end;
  
  if (!timespec_get(&end, TIME_UTC)) {
    c7_error("Failed getting time: %d", errno);
    return 0;
  }
  
  return
    (end.tv_sec - timer->start.tv_sec) * 1000000000 +
    (end.tv_nsec - timer->start.tv_nsec);
}

uint64_t c7_timer_usecs(const struct c7_timer *timer) {
  return c7_timer_nsecs(timer) / 1000;
}
