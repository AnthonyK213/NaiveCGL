#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/Surface.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Surface_eval(const Naive_Surface_t surface, const double u,
                                const double v, const int n_deriv,
                                int *const n_result,
                                Naive_Vector3d_t *const result) {
  if (!n_result)
    return Naive_Code_null_arg_address;

  if (n_deriv < 0)
    return Naive_Code_invalid_value;

  *n_result = (n_deriv + 1) * (n_deriv + 2) >> 1;

  if (result) {
    Naive_ROSTER_ASK(Naive_Surface, surface, H);
    Naive_Vec3dList1 aD{};
    Naive_Code aCode = H->Evaluate(u, v, n_deriv, aD);
    if (aCode)
      return aCode;

    for (Naive_Integer i = 0; i < *n_result; ++i) {
      aD[i].Dump(result[i]);
    }
  }

  return Naive_Code_ok;
}
