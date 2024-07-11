#include <naivecgl/Common/TObject.h>
#include <naivecgl/Geometry/Geometry.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Geometry_is_valid(Naive_Geometry_t geometry,
                                     Naive_Logical_t *const is_valid) {
  if (!is_valid)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Geometry, geometry, H);
  *is_valid = H->IsValid();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Geometry_clone(Naive_Geometry_t geometry,
                                  Naive_Geometry_t *const clone) {
  if (!clone)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Geometry, geometry, H);
  Naive_ROSTER_ADD(H->Clone(), *clone);
  return Naive_Code_ok;
}
