#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/Surface.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Surface_eval(Naive_Surface_t surface, double u, double v,
                                int n_u_deriv, int n_v_deriv,
                                Naive_Vector3d_t p[]) {
  if (!p)
    return Naive_Code_null_arg_address;

  if (n_u_deriv < 0 || n_u_deriv > 3 || n_v_deriv < 0 || n_v_deriv > 3)
    return Naive_Code_value_out_of_range;

  Naive_Integer n_deriv = n_u_deriv + n_v_deriv;
  Naive_ROSTER_ASK(Naive_Surface, surface, H);
  Naive_Vec3dList1 deriv{};
  Naive_CHECK_CODE(H->Evaluate(u, v, n_deriv, deriv));

  Naive_Integer index = 0;
  for (Naive_Integer j = 0; j <= n_v_deriv; ++j) {
    for (Naive_Integer i = 0; i <= n_u_deriv; ++i) {
      deriv[(i + j) * (i + j + 1) / 2 + j].Dump(p[index++]);
    }
  }

  return Naive_Code_ok;
}
