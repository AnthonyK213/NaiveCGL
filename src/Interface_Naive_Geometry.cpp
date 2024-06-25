#include <naivecgl/Geometry/Geometry.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Geometry_is_valid(const Naive_Geometry_t geometry,
                                     Naive_Logical_t *const is_valid) {
  if (!is_valid)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Geometry, geometry, H);
  *is_valid = H->IsValid();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Geometry_clone(const Naive_Geometry_t geometry,
                                  Naive_Geometry_t *const clone) {
  if (!clone)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Geometry, geometry, H);
  Handle_Naive_Geometry aClone = H->Clone();
  aClone->IncrementRefCounter();
  *clone = aClone.get();
  return Naive_Code_ok;
}
