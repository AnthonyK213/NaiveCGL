#include <naivecgl/Common/Roster.h>
#include <naivecgl/Tessellation/Sphere.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Tessellation_make_tetrasphere(const Naive_Point3d_t *center,
                                                 double radius, int level,
                                                 Naive_Poly_t *const poly) {
  if (!center || !poly)
    return Naive_Code_null_arg_address;

  if (radius <= ::naivecgl::math::Precision::Epsilon0() || level < 0)
    return Naive_Code_value_out_of_range;

  Naive_Pnt3d aCenter{*center};
  Handle_Naive_Poly aPoly =
      ::naivecgl::tessellation::Sphere::TetraSphere(aCenter, radius, level);
  if (!aPoly)
    return Naive_Code_err;

  Naive_ROSTER_ADD(aPoly, *poly);
  return Naive_Code_ok;
}
