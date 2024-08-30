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

  int u_degree = nurbs_surface_sf->u_degree;
  int v_degree = nurbs_surface_sf->v_degree;
  int n_u_vertices = nurbs_surface_sf->n_u_vertices;
  int n_v_vertices = nurbs_surface_sf->n_v_vertices;
  int vertex_dim = nurbs_surface_sf->vertex_dim;
  double *vertex = nurbs_surface_sf->vertex;
  int n_u_knots = nurbs_surface_sf->n_u_knots;
  int n_v_knots = nurbs_surface_sf->n_v_knots;
  int *u_knot_mult = nurbs_surface_sf->u_knot_mult;
  int *v_knot_mult = nurbs_surface_sf->v_knot_mult;
  double *u_knot = nurbs_surface_sf->u_knot;
  double *v_knot = nurbs_surface_sf->v_knot;

  if (!vertex || !u_knot_mult || !v_knot_mult || !u_knot || !v_knot)
    return Naive_Code_invalid_value;

  if (n_u_knots < 2 || n_v_knots < 2)
    return Naive_Code_insufficient_knots;

  if (u_degree < 1 || v_degree < 1)
    return Naive_Code_value_out_of_range;

  int n_u_poles = n_u_vertices / vertex_dim;
  if (n_u_poles < 2)
    return Naive_Code_insufficient_points;

  int n_v_poles = n_v_vertices / vertex_dim;
  if (n_v_poles < 2)
    return Naive_Code_insufficient_points;

  if (nurbs_surface_sf->is_rational && vertex_dim == 4) {
    Naive_Pnt3dList2 aPoles{};
    Naive_RealList2 aWeights{};
    aPoles.reserve(n_u_poles);
    aWeights.reserve(n_u_poles);

    for (Naive_Integer i = 0; i < n_u_poles; ++i) {
      Naive_Pnt3dList1 aVP(n_v_poles, Naive_Pnt3d::Unset());
      Naive_RealList1 aVW{};
      aVW.reserve(n_v_poles);

      for (Naive_Pnt3d &aP : aVP) {
        aP.SetX(*(vertex++));
        aP.SetY(*(vertex++));
        aP.SetZ(*(vertex++));
        Naive_Real aWeight = *(vertex++);
        if (!aP.Divide(aWeight))
          return Naive_Code_invalid_value;
        aVW.push_back(aWeight);
      }

      aPoles.emplace_back(::std::move(aVP));
      aWeights.emplace_back(::std::move(aVW));
    }

    Naive_RealList1 aUKnots(u_knot, u_knot + n_u_knots);
    Naive_RealList1 aVKnots(v_knot, v_knot + n_v_knots);
    Naive_IntegerList1 aUMults(u_knot_mult, u_knot_mult + n_u_knots);
    Naive_IntegerList1 aVMults(v_knot_mult, v_knot_mult + n_v_knots);

    Handle_Naive_NurbsSurface aSrf = new Naive_NurbsSurface;
    Naive_CHECK_CODE(aSrf->Init(aPoles, aWeights, aUKnots, aVKnots, aUMults,
                                aVMults, u_degree, v_degree));

    Naive_ROSTER_ADD(aSrf, *nurbs_surface);
    return Naive_Code_ok;
  } else if (!nurbs_surface_sf->is_rational && vertex_dim == 3) {
    Naive_Pnt3dList2 aPoles{};
    Naive_RealList2 aWeights(n_u_poles, Naive_RealList1(n_v_poles, 1.));
    aPoles.reserve(n_u_poles);

    for (Naive_Integer i = 0; i < n_u_poles; ++i) {
      Naive_Pnt3dList1 aVP(n_v_poles, Naive_Pnt3d::Unset());

      for (Naive_Pnt3d &aP : aVP) {
        aP.SetX(*(vertex++));
        aP.SetY(*(vertex++));
        aP.SetZ(*(vertex++));
      }

      aPoles.emplace_back(::std::move(aVP));
    }

    Naive_RealList1 aUKnots(u_knot, u_knot + n_u_knots);
    Naive_RealList1 aVKnots(v_knot, v_knot + n_v_knots);
    Naive_IntegerList1 aUMults(u_knot_mult, u_knot_mult + n_u_knots);
    Naive_IntegerList1 aVMults(v_knot_mult, v_knot_mult + n_v_knots);

    Handle_Naive_NurbsSurface aSrf = new Naive_NurbsSurface;
    Naive_CHECK_CODE(aSrf->Init(aPoles, aWeights, aUKnots, aVKnots, aUMults,
                                aVMults, u_degree, v_degree));

    Naive_ROSTER_ADD(aSrf, *nurbs_surface);
    return Naive_Code_ok;
  } else {
    return Naive_Code_bad_dimension;
  }
}
