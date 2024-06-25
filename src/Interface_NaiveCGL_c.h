#ifndef _NaiveCGL_Interface_NaiveCGL_c_HeaderFile_1
#define _NaiveCGL_Interface_NaiveCGL_c_HeaderFile_1

#include <naivecgl/Interface/NaiveCGL_c.h>

#define Naive_H_CAST(T, H, N) T *N = reinterpret_cast<T *>(H);
#define Naive_H_CAST_AND_CHECK(T, H, N)                                        \
  Naive_H_CAST(T, H, N);                                                       \
  if (!N) {                                                                    \
    return Naive_Code_invalid_handle;                                          \
  }

#endif
