#include "Interface_NaiveCGL_c.h"

// TODO: Registered by application?

Naive_Code_t Naive_Memory_alloc(size_t nbytes, void **const pointer) {
  *pointer = malloc(nbytes);
  return Naive_Code_ok;
}

Naive_Code_t Naive_Memory_free(void *pointer) {
  free(pointer);
  return Naive_Code_ok;
}
