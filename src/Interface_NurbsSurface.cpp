#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/NurbsSurface.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t
Naive_NurbsSurface_ask(Naive_NurbsSurface_t nurbs_surface,
                       Naive_NurbsSurface_sf_t *const nurbs_surface_sf) {
  if (!nurbs_surface_sf)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_NurbsSurface, nurbs_surface, H);

  if (!H->IsValid())
    return Naive_Code_invalid_object;

  nurbs_surface_sf->u_degree = H->UDegree();
  nurbs_surface_sf->v_degree = H->VDegree();
  nurbs_surface_sf->is_rational = H->IsURational() || H->IsVRational();
  nurbs_surface_sf->vertex_dim = nurbs_surface_sf->is_rational ? 4 : 3;
  nurbs_surface_sf->form = Naive_NurbsSurface_form_unset_c;
  nurbs_surface_sf->is_u_periodic = H->IsUPeriodic();
  nurbs_surface_sf->is_v_periodic = H->IsVPeriodic();
  nurbs_surface_sf->is_u_closed = H->IsUClosed();
  nurbs_surface_sf->is_v_closed = H->IsVClosed();

  /* TODO: Arrays. */

  nurbs_surface_sf->vertex = nullptr;
  nurbs_surface_sf->u_knot_mult = nullptr;
  nurbs_surface_sf->v_knot_mult = nullptr;
  nurbs_surface_sf->u_knot = nullptr;
  nurbs_surface_sf->v_knot = nullptr;

  return Naive_Code_ok;
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
