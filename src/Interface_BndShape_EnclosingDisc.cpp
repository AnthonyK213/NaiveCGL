#include <naivecgl/BndShape/EnclosingDisc.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t
Naive_BndShape_EnclosingDisc_new(Naive_EnclosingDisc_t *const enclosing_disc) {
  if (!enclosing_disc)
    return Naive_Code_null_arg_address;

  Naive_Handle<::naivecgl::bndshape::EnclosingDisc> aED =
      new ::naivecgl::bndshape::EnclosingDisc();
  Naive_ROSTER_ADD(aED);
  *enclosing_disc = aED->Tag();
  return Naive_Code_ok;
}

Naive_Code_t
Naive_BndShape_EnclosingDisc_rebuild(Naive_EnclosingDisc_t enclosing_disc,
                                     const int n_points,
                                     const Naive_Point2d_t *points) {
  if (!points)
    return Naive_Code_null_arg_address;

  if (n_points < 0)
    return Naive_Code_invalid_value;

  Naive_ROSTER_ASK(::naivecgl::bndshape::EnclosingDisc, enclosing_disc, H);
  Naive_Pnt2dList1 aPoints(points, points + n_points);
  H->ReBuild(aPoints);
  return Naive_Code_ok;
}

Naive_Code_t
Naive_BndShape_EnclosingDisc_ask_circle(Naive_EnclosingDisc_t enclosing_disc,
                                        Naive_Point2d_t *const theOrigin,
                                        double *const theR) {
  if (!theOrigin || !theR)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(::naivecgl::bndshape::EnclosingDisc, enclosing_disc, H);
  Naive_Pnt2d anOrigin;
  Naive_Real aR;
  if (!H->Result(anOrigin, aR))
    return Naive_Code_err;

  anOrigin.Dump(*theOrigin);
  *theR = aR;
  return Naive_Code_ok;
}
