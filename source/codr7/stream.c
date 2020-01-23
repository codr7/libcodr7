#include <errno.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

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

void c7_stream_printf(struct c7_stream *stream, const char *spec, ...) {
  va_list args;
  va_start(args, spec);

  va_list len_args;
  va_copy(len_args, args);
  int len = vsnprintf(NULL, 0, spec, len_args);
  va_end(len_args);

  c7_stream_grow(stream, stream->length + len);
  vsnprintf(stream->data + stream->length, len + 1, spec, args);
  va_end(args);
  stream->length += len;
}

void c7_stream_putc(struct c7_stream *stream, char value) {
  c7_stream_grow(stream, stream->length + 1);
  stream->data[stream->length++] = value;
  stream->data[stream->length] = 0;
}

void c7_stream_puts(struct c7_stream *stream, const char *value) {
  size_t len = strlen(value);
  c7_stream_grow(stream, stream->length + len);
  strncpy(stream->data + stream->length, value, len+1);
  stream->length += len;
}

char *c7_stream_getline(struct c7_stream *stream, FILE *in) {
  uint64_t start = stream->length;

  for (;;) {
    char c = fgetc(in);

    if (c == EOF) {
      if (ferror(in)) {
	c7_error("Failed reading char: %d", errno);
      } else {
	break;
      }
    }
    
    c7_stream_putc(stream, c);

    if (c == '\n') {
      break;
    }
  }

  return stream->data ? stream->data + start : NULL;
}
