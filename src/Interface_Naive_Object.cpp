#include <naivecgl/Common/TObject.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Object_free(Naive_Object_t object) {
  return _Naive_Roster_del(object);
}
