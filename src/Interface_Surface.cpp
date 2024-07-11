#include <naivecgl/Common/TObject.h>
#include <naivecgl/Geometry/Surface.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Surface_evaluate(const Naive_Surface_t surface,
                                    const double u, const double v,
                                    const int n_derivative, int *const n_result,
                                    Naive_Vector3d_t *const result) {
  if (!n_result)
    return Naive_Code_null_arg_address;

  if (n_derivative < 0)
    return Naive_Code_invalid_value;

  *n_result = (n_derivative + 1) * (n_derivative + 2) >> 1;

  if (result) {
    Naive_ROSTER_ASK(Naive_Surface, surface, H);
    Naive_Vec3dList1 aD{};
    Naive_Code aCode = H->Evaluate(u, v, n_derivative, aD);
    if (aCode)
      return aCode;

    for (Naive_Integer i = 0; i < *n_result; ++i) {
      aD[i].Dump(result[i]);
    }
  }

  return Naive_Code_ok;
}
