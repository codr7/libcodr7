#include <errno.h>
#include <stdlib.h>

#include "codr7/error.h"
#include "codr7/stream.h"

struct c7_stream *c7_stream_init(struct c7_stream *stream) {
  stream->data = NULL;
  stream->length = stream->capacity = 0;
  return stream;
}

void c7_stream_deinit(struct c7_stream *stream) {
  if (stream->data) { free(stream->data); }
}

void c7_stream_reset(struct c7_stream *stream) {
  if (stream->data) {
    stream->length = 0;
    stream->data[0] = 0;
  }
}

void c7_stream_grow(struct c7_stream *stream, uint64_t length) {
  if (stream->capacity) {
    while (stream->capacity < length + 1) {
      stream->capacity *= 2;
    }
  } else {
    stream->capacity = length + 1;
  }

  stream->data = realloc(stream->data, stream->capacity);
}

void c7_stream_putc(struct c7_stream *stream, char c) {
  c7_stream_grow(stream, stream->length + 1);
  stream->data[stream->length++] = c;
  stream->data[stream->length] = 0;
}

char *c7_stream_getline(struct c7_stream *stream, FILE *in) {
  char *start = stream->data ? stream->data + stream->length : NULL;

  for (;;) {
    char c = fgetc(in);

    if (ferror(in)) {
      c7_error("Failed reading char: %d", errno);
    }
    
    if (c == '\n' || c == EOF) {
      break;
    }

    c7_stream_putc(stream, c);
  }

  return start ? start : stream->data;
}
