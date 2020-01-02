#ifndef C7_ERROR_H
#define C7_ERROR_H

#include <stdio.h>
#include <stdlib.h>

#define c7_error(spec, ...)				\
  fprintf(stderr, "Error in %s, line %d:\n" spec,	\
	  __FILE__, __LINE__, ##__VA_ARGS__);		\
  abort();					  

#endif
