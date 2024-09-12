#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/NurbsSurface.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t
Naive_NurbsSurface_ask(Naive_NurbsSurface_t nurbs_surface,
                       Naive_NurbsSurface_sf_t *const nurbs_surface_sf) {
  if (!nurbs_surface_sf)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_NurbsSurface, nurbs_surface, H);
  return H->Dump(*nurbs_surface_sf, Naive_default_mem_handler());
}

Naive_Code_t
Naive_NurbsSurface_create(const Naive_NurbsSurface_sf_t *nurbs_surface_sf,
                          Naive_NurbsSurface_t *const nurbs_surface) {
  if (!nurbs_surface_sf || !nurbs_surface)
    return Naive_Code_null_arg_address;

  Handle_Naive_NurbsSurface aSrf = new Naive_NurbsSurface;
  Naive_CHECK_CODE(aSrf->Init(*nurbs_surface_sf));
  Naive_ROSTER_ADD(aSrf, *nurbs_surface);
  return Naive_Code_ok;
}
