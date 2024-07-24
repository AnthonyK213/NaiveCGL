#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/Curve.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Curve_ask_bound(Naive_Curve_t curve,
                                   Naive_Interval_t *const bound) {
  if (!bound)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Curve, curve, H);
  if (!H->IsValid())
    return Naive_Code_invalid_object;
  bound->t0 = H->FirstParameter();
  bound->t1 = H->LastParameter();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Curve_eval(Naive_Curve_t curve, double t, int n_deriv,
                              Naive_Vector3d_t p[]) {
  if (!p)
    return Naive_Code_null_arg_address;

  if (n_deriv < 0 || n_deriv > 4)
    return Naive_Code_value_out_of_range;

  Naive_ROSTER_ASK(Naive_Curve, curve, H);
  Naive_Vec3dList1 aD{};
  Naive_CHECK_CODE(H->Evaluate(t, n_deriv, aD));

  for (Naive_Integer i = 0; i < aD.size(); ++i) {
    aD[i].Dump(p[i]);
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_Curve_eval_curvature(Naive_Curve_t curve, double t,
                                        Naive_Vector3d_t *const curvature) {
  if (!curvature)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Curve, curve, H);
  Naive_Vec3d aCurvature;
  Naive_CHECK_CODE(H->CurvatureAt(t, aCurvature));
  aCurvature.Dump(*curvature);
  return Naive_Code_ok;
}

Naive_Code_t Naive_Curve_make_wire_body(
    int n_curves, const Naive_Curve_t curves[], const Naive_Interval_t bounds[],
    const Naive_Curve_make_wire_body_o_t *options, Naive_Body_t *const body,
    int *const n_new_edges, Naive_Edge_t **const new_edges,
    int **const edge_index) {
  if (n_curves <= 0)
    return Naive_Code_value_out_of_range;

  if (!curves || !bounds || !options || !body || !n_new_edges || !new_edges ||
      !edge_index)
    return Naive_Code_null_arg_address;

  return Naive_Code_not_implemented;
}
