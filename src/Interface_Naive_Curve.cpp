#include <naivecgl/Geometry/Curve.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Curve_ask_bound(const Naive_Curve_t curve,
                                   Naive_Interval_t *const bound) {
  if (!bound)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Curve, curve, H);
  if (!H->IsValid())
    return Naive_Code_invalid_handle;
  bound->t0 = H->FirstParameter();
  bound->t1 = H->LastParameter();
  return Naive_Code_ok;
}

Naive_Code_t Naive_Curve_evaluate(const Naive_Curve_t curve, const double t,
                                  const int n_derivative, int *const n_result,
                                  Naive_Vector3d_t *const result) {
  if (!n_result)
    return Naive_Code_null_arg_address;

  if (n_derivative < 0)
    return Naive_Code_value_out_of_range;

  *n_result = n_derivative + 1;

  if (result) {
    Naive_H_CAST_AND_CHECK(const Naive_Curve, curve, H);
    Naive_Vec3dList1 aD{};
    Naive_Code aCode = H->DerivativeAt(t, n_derivative, aD);
    if (aCode)
      return aCode;

    for (Naive_Integer i = 0; i < *n_result; ++i) {
      aD[i].Dump(result[i]);
    }
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_Curve_curvature_at(const Naive_Curve_t curve, const double t,
                                      Naive_Vector3d_t *const curvature) {
  if (!curvature)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_Curve, curve, H);
  Naive_Vec3d aCurvature;
  Naive_Code aCode = H->CurvatureAt(t, aCurvature);
  if (aCode)
    return aCode;
  aCurvature.Dump(*curvature);
  return Naive_Code_ok;
}
