#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/Surface.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_Surface_eval(Naive_Surface_t surface, Naive_UV_t uv,
                                int n_u_derivs, int n_v_derivs,
                                Naive_Vec3d_t p[]) {
  if (!p)
    return Naive_Code_null_arg_address;

  if (n_u_derivs < 0 || n_u_derivs > 3 || n_v_derivs < 0 || n_v_derivs > 3)
    return Naive_Code_value_out_of_range;

  Naive_Integer n_derivs = n_u_derivs + n_v_derivs;
  Naive_ROSTER_ASK(Naive_Surface, surface, H);
  Naive_Vec3dList2 deriv{};
  Naive_CHECK_CODE(H->Evaluate(uv.x, uv.y, n_derivs, deriv));

  Naive_Integer index = 0;
  for (Naive_Integer j = 0; j <= n_v_derivs; ++j) {
    for (Naive_Integer i = 0; i <= n_u_derivs; ++i) {
      deriv[i][j].Dump(p[index++]);
    }
  }

  return Naive_Code_ok;
}
