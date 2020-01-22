#ifndef C7_STREAM_H
#define C7_STREAM_H

#include <stdint.h>
#include <stdio.h>

struct c7_stream {
  char *data;
  uint64_t capacity, length;
};

struct c7_stream *c7_stream_init(struct c7_stream *stream);
void c7_stream_deinit(struct c7_stream *stream);

void c7_stream_reset(struct c7_stream *stream);
void c7_stream_grow(struct c7_stream *stream, uint64_t length);
void c7_stream_putc(struct c7_stream *stream, char value);
void c7_stream_puts(struct c7_stream *stream, const char *value);
char *c7_stream_getline(struct c7_stream *stream, FILE *in);

#endif
