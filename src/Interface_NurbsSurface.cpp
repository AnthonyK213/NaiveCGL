#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/NurbsSurface.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_NurbsSurface_ask_degree(Naive_NurbsSurface_t nurbs_surface,
                                           int *const degree_u,
                                           int *const degree_v) {
  Naive_ROSTER_ASK(Naive_NurbsSurface, nurbs_surface, H);
  if (degree_u)
    *degree_u = H->UDegree();
  if (degree_v)
    *degree_v = H->VDegree();
  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsSurface_new(
    const int n_poles_u, const int n_poles_v, const Naive_Point3d_t *poles,
    const int n_weights_u, const int n_weights_v, const double *weights,
    const int n_knots_u, const double *knots_u, const int n_knots_v,
    const double *knots_v, const int n_mults_u, const int *mults_u,
    const int n_mults_v, const int *mults_v, const int degree_u,
    const int degree_v, Naive_NurbsSurface_t *const nurbs_surface) {
  if (!poles || !weights || !knots_u || !knots_v || !mults_u || !mults_v ||
      !nurbs_surface)
    return Naive_Code_null_arg_address;

  if (n_poles_u < 2 || n_poles_v < 2 || n_weights_u < 2 || n_weights_v < 2 ||
      n_knots_u < 2 || n_knots_v < 2 || n_mults_u < 2 || n_mults_v < 2 ||
      degree_u < 1 || degree_v < 1)
    return Naive_Code_value_out_of_range;

  Naive_Pnt3dList2 aPoles{};
  aPoles.reserve(n_poles_u);
  const Naive_Point3d_t *aPHead = poles;
  for (Naive_Integer i = 0; i < n_poles_u; ++i, aPHead += n_poles_v) {
    Naive_Pnt3dList1 aVP(aPHead, aPHead + n_poles_v);
    aPoles.emplace_back(::std::move(aVP));
  }
  Naive_RealList2 aWeights{};
  aWeights.reserve(n_weights_u);
  const Naive_Real *aWHead = weights;
  for (Naive_Integer i = 0; i < n_weights_u; ++i, aWHead += n_weights_v) {
    Naive_RealList1 aVW(aWHead, aWHead + n_weights_v);
    aWeights.emplace_back(::std::move(aVW));
  }
  Naive_RealList1 aUKnots(knots_u, knots_u + n_knots_u);
  Naive_RealList1 aVKnots(knots_v, knots_v + n_knots_v);
  Naive_IntegerList1 aUMults(mults_u, mults_u + n_mults_u);
  Naive_IntegerList1 aVMults(mults_v, mults_v + n_mults_v);

  Handle_Naive_NurbsSurface aSrf = new Naive_NurbsSurface;
  Naive_CHECK_CODE(aSrf->Init(aPoles, aWeights, aUKnots, aVKnots, aUMults,
                              aVMults, degree_u, degree_v));

  Naive_ROSTER_ADD(aSrf, *nurbs_surface);
  return Naive_Code_ok;
}
