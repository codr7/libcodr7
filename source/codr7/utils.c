#include <stdlib.h>
#include <string.h>
#include "codr7/utils.h"

char *c7_strdup(const char *in) {
  size_t l = strlen(in) + 1;
  char *out = malloc(l);
  strcpy(out, in);
  return out;
}
