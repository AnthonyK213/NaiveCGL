#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Memory_free(void *pointer) {
  // TODO: Application specific?
  free(pointer);
  return Naive_Code_ok;
}
