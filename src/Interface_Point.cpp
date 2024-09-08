#include "Interface_NaiveCGL_c.h"

#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/Point3d.h>

Naive_Code_t Naive_Point_ask(Naive_Point_t point,
                             Naive_Point_sf_t *const point_sf) {
  if (!point_sf)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Point3d, point, H);
  return H->Dump(*point_sf);
}

Naive_Code_t Naive_Point_create(const Naive_Point_sf_t *point_sf,
                                Naive_Point_t *const point) {
  if (!point_sf || !point)
    return Naive_Code_null_arg_address;

  Handle_Naive_Point3d aPoint = new Naive_Point3d(*point_sf);
  Naive_ROSTER_ADD(aPoint, *point);
  return Naive_Code_ok;
}
