#include <naivecgl/Common/Object.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Object_free(Naive_Object_t Object) {
  Naive_H_CAST(Naive_Object, Object, H);
  if (H && H->DecrementRefCounter() == 0)
    H->Delete();
  return Naive_Code_ok;
}
