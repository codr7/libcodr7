#include "codr7/timer.h"

void c7_timer_reset(struct c7_timer *timer) {
  timespec_get(&timer->start, TIME_UTC);
}

uint64_t c7_timer_nsecs(const struct c7_timer *timer) {
  struct timespec end;
  timespec_get(&end, TIME_UTC);
  
  return
    (end.tv_sec - timer->start.tv_sec) * 1000000000 +
    (end.tv_nsec - timer->start.tv_nsec);
}

uint64_t c7_timer_usecs(const struct c7_timer *timer) {
  return c7_timer_nsecs(timer) / 1000;
}
