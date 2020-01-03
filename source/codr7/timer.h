#ifndef C7_TIMER_H
#define C7_TIMER_H

#include <stdint.h>
#include <time.h>

struct c7_timer {
  struct timespec start;
};

void c7_timer_reset(struct c7_timer *timer);
uint64_t c7_timer_nsecs(struct c7_timer *timer);

#endif
