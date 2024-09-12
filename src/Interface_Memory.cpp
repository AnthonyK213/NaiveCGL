#include "Interface_NaiveCGL_c.h"

/* TODO: Registered by application? */

Naive_Code_t Naive_Memory_alloc(size_t nbytes, void **const pointer) {
  *pointer = malloc(nbytes);
  return Naive_Code_ok;
}

Naive_Code_t Naive_Memory_free(void *pointer) {
  free(pointer);
  return Naive_Code_ok;
}

const ::naivecgl::common::MemHandler &Naive_default_mem_handler() {
  static ::naivecgl::common::MemHandler handler{
      [](Naive_Size nbytes, void **const pointer) {
        return static_cast<Naive_Code>(Naive_Memory_alloc(nbytes, pointer));
      },
      [](void *pointer) {
        return static_cast<Naive_Code>(Naive_Memory_free(pointer));
      }};
  return handler;
}
