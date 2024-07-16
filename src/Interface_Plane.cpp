#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/Plane.h>
#include <naivecgl/Math/Util.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Plane_new(const Naive_Plane_sf_t *plane_sf,
                             Naive_Plane_t *const plane) {
  if (!plane_sf || !plane)
    return Naive_Code_null_arg_address;

  Handle_Naive_Plane aPlane = new Naive_Plane(*plane_sf);
  Naive_ROSTER_ADD(aPlane, *plane);
  return Naive_Code_ok;
}

Naive_Code_t Naive_Plane_ask(const Naive_Plane_t plane,
                             Naive_Plane_sf_t *const plane_sf) {
  if (!plane_sf)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Plane, plane, H);
  return (H->Pln().Dump(*plane_sf)) ? Naive_Code_ok : Naive_Code_invalid_object;
}

Naive_Code_t Naive_Plane_distance(const Naive_Plane_t plane,
                                  const Naive_Point3d_t *point,
                                  double *const distance) {
  if (!point)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Plane, plane, H);
  double aDistance = H->Distance(*point);
  if (!::naivecgl::math::Util::IsValidReal(aDistance))
    return Naive_Code_invalid_value;
  *distance = aDistance;
  return Naive_Code_ok;
}
