#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/NurbsCurve.h>
#include <naivecgl/Geometry2d/NurbsCurve.h>

#include "Interface_NaiveCGL_c.h"

#define Naive_ASK_KNOTS(Crv_, NbKnots_, Knots_, Mults_)                        \
  Naive_Integer nbKnots = Crv_->NbKnots();                                     \
  if (nbKnots <= 0)                                                            \
    return Naive_Code_invalid_object;                                          \
  *(NbKnots_) = nbKnots;                                                       \
  if (Knots_) {                                                                \
    const Naive_RealList1 &aKnots = Crv_->Knots();                             \
    Naive_ALLOC_ARRAY(double, nbKnots, Knots_);                                \
    ::std::copy(aKnots.cbegin(), aKnots.cend(), *(Knots_));                    \
  }                                                                            \
  if (Knots_) {                                                                \
    const Naive_IntegerList1 &aMults = Crv_->Multiplicities();                 \
    Naive_ALLOC_ARRAY(int, nbKnots, Mults_);                                   \
    ::std::copy(aMults.cbegin(), aMults.cend(), *(Mults_));                    \
  }

Naive_Code_t Naive_NurbsCurve_add_knot(Naive_NurbsCurve_t nurbs_curve, double t,
                                       int mult) {
  Naive_ROSTER_ASK(Naive_Object, nurbs_curve, Obj);

  if (Obj->GetClassType()->IsSubClass(Naive_CLASS(Naive_NurbsCurve))) {
    Handle_Naive_NurbsCurve H = Handle_Naive_NurbsCurve::DownCast(Obj);
    return H->InsertKnot(t, mult);
  } else if (Obj->GetClassType()->IsSubClass(Naive_CLASS(Naive_NurbsCurve2d))) {
    Handle_Naive_NurbsCurve2d H = Handle_Naive_NurbsCurve2d::DownCast(Obj);
    return H->InsertKnot(t, mult);
  } else {
    return Naive_Code_invalid_tag;
  }
}

Naive_Code_t Naive_NurbsCurve_ask(Naive_NurbsCurve_t nurbs_curve,
                                  Naive_NurbsCurve_sf_t *const nurbs_curve_sf) {
  if (!nurbs_curve_sf)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Object, nurbs_curve, Obj);

  if (Obj->GetClassType()->IsSubClass(Naive_CLASS(Naive_NurbsCurve))) {
    Handle_Naive_NurbsCurve H = Handle_Naive_NurbsCurve::DownCast(Obj);

    if (!H->IsValid())
      return Naive_Code_invalid_object;

    const Naive_Pnt3dList1 &aPoles = H->Poles();
    const Naive_RealList1 &aWeights = H->Weights();
    const Naive_RealList1 &aKnots = H->Knots();
    const Naive_IntegerList1 &aMults = H->Multiplicities();

    nurbs_curve_sf->degree = H->Degree();
    nurbs_curve_sf->vertex_dim = H->IsRational() ? 4 : 3;
    nurbs_curve_sf->is_rational = H->IsRational();
    nurbs_curve_sf->form = Naive_NurbsCurve_form_unset_c;
    nurbs_curve_sf->is_periodic = H->IsPeriodic();
    nurbs_curve_sf->is_closed = H->IsClosed();

    nurbs_curve_sf->n_vertices = nurbs_curve_sf->vertex_dim * aPoles.size();
    nurbs_curve_sf->n_knots = static_cast<int>(aKnots.size());

    Naive_unique_ptr<double> vertex{}, knot{};
    Naive_unique_ptr<int> knot_mult{};

    Naive_ALLOC_ARRAY(double, nurbs_curve_sf->n_vertices, &vertex);
    Naive_ALLOC_ARRAY(double, nurbs_curve_sf->n_knots, &knot);
    Naive_ALLOC_ARRAY(int, nurbs_curve_sf->n_knots, &knot_mult);

    double *p_vertex = vertex.get();

    if (H->IsRational()) {
      Naive_Real aWeight;
      for (Naive_Integer i = 0; i < aPoles.size(); ++i) {
        aWeight = aWeights[i];
        *(p_vertex++) = aPoles[i].X() * aWeight;
        *(p_vertex++) = aPoles[i].Y() * aWeight;
        *(p_vertex++) = aPoles[i].Z() * aWeight;
        *(p_vertex++) = aWeight;
      }
    } else {
      for (Naive_Integer i = 0; i < aPoles.size(); ++i) {
        *(p_vertex++) = aPoles[i].X();
        *(p_vertex++) = aPoles[i].Y();
        *(p_vertex++) = aPoles[i].Z();
      }
    }

    ::std::copy(aKnots.cbegin(), aKnots.cend(), knot.get());
    ::std::copy(aMults.cbegin(), aMults.cend(), knot_mult.get());

    nurbs_curve_sf->vertex = vertex.release();
    nurbs_curve_sf->knot = knot.release();
    nurbs_curve_sf->knot_mult = knot_mult.release();
  } else if (Obj->GetClassType()->IsSubClass(Naive_CLASS(Naive_NurbsCurve2d))) {
    Handle_Naive_NurbsCurve2d H = Handle_Naive_NurbsCurve2d::DownCast(Obj);

    if (!H->IsValid())
      return Naive_Code_invalid_object;

    const Naive_Pnt2dList1 &aPoles = H->Poles();
    const Naive_RealList1 &aWeights = H->Weights();
    const Naive_RealList1 &aKnots = H->Knots();
    const Naive_IntegerList1 &aMults = H->Multiplicities();

    nurbs_curve_sf->degree = H->Degree();
    nurbs_curve_sf->vertex_dim = H->IsRational() ? 3 : 2;
    nurbs_curve_sf->is_rational = H->IsRational();
    nurbs_curve_sf->form = Naive_NurbsCurve_form_unset_c;
    nurbs_curve_sf->is_periodic = H->IsPeriodic();
    nurbs_curve_sf->is_closed = H->IsClosed();

    nurbs_curve_sf->n_vertices = nurbs_curve_sf->vertex_dim * aPoles.size();
    nurbs_curve_sf->n_knots = static_cast<int>(aKnots.size());

    Naive_unique_ptr<double> vertex{}, knot{};
    Naive_unique_ptr<int> knot_mult{};

    Naive_ALLOC_ARRAY(double, nurbs_curve_sf->n_vertices, &vertex);
    Naive_ALLOC_ARRAY(double, nurbs_curve_sf->n_knots, &knot);
    Naive_ALLOC_ARRAY(int, nurbs_curve_sf->n_knots, &knot_mult);

    double *p_vertex = vertex.get();

    if (H->IsRational()) {
      Naive_Real aWeight;
      for (Naive_Integer i = 0; i < aPoles.size(); ++i) {
        aWeight = aWeights[i];
        *(p_vertex++) = aPoles[i].X() * aWeight;
        *(p_vertex++) = aPoles[i].Y() * aWeight;
        *(p_vertex++) = aWeight;
      }
    } else {
      for (Naive_Integer i = 0; i < aPoles.size(); ++i) {
        *(p_vertex++) = aPoles[i].X();
        *(p_vertex++) = aPoles[i].Y();
      }
    }

    ::std::copy(aKnots.cbegin(), aKnots.cend(), knot.get());
    ::std::copy(aMults.cbegin(), aMults.cend(), knot_mult.get());

    nurbs_curve_sf->vertex = vertex.release();
    nurbs_curve_sf->knot = knot.release();
    nurbs_curve_sf->knot_mult = knot_mult.release();
  } else {
    return Naive_Code_invalid_tag;
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_knots(Naive_NurbsCurve_t nurbs_curve,
                                        int *const n_knots,
                                        double **const knots,
                                        int **const multiplicities) {
  if (!n_knots)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_Object, nurbs_curve, Obj);

  if (Obj->GetClassType()->IsSubClass(Naive_CLASS(Naive_NurbsCurve))) {
    Handle_Naive_NurbsCurve H = Handle_Naive_NurbsCurve::DownCast(Obj);
    Naive_ASK_KNOTS(H, n_knots, knots, multiplicities);
  } else if (Obj->GetClassType()->IsSubClass(Naive_CLASS(Naive_NurbsCurve2d))) {
    Handle_Naive_NurbsCurve2d H = Handle_Naive_NurbsCurve2d::DownCast(Obj);
    Naive_ASK_KNOTS(H, n_knots, knots, multiplicities);
  } else {
    return Naive_Code_invalid_tag;
  }

  return Naive_Code_ok;
}

Naive_Code_t
Naive_NurbsCurve_create(const Naive_NurbsCurve_sf_t *nurbs_curve_sf,
                        Naive_NurbsCurve_t *const nurbs_curve) {
  if (!nurbs_curve_sf || !nurbs_curve)
    return Naive_Code_null_arg_address;

  if ((nurbs_curve_sf->is_rational && nurbs_curve_sf->vertex_dim == 3) ||
      (!nurbs_curve_sf->is_rational && nurbs_curve_sf->vertex_dim == 2)) {
    Handle_Naive_NurbsCurve2d aCrv = new Naive_NurbsCurve2d;
    Naive_CHECK_CODE(aCrv->Init(*nurbs_curve_sf));
    Naive_ROSTER_ADD(aCrv, *nurbs_curve);
    return Naive_Code_ok;
  }

  if ((nurbs_curve_sf->is_rational && nurbs_curve_sf->vertex_dim == 4) ||
      (!nurbs_curve_sf->is_rational && nurbs_curve_sf->vertex_dim == 3)) {
    Handle_Naive_NurbsCurve aCrv = new Naive_NurbsCurve;
    Naive_CHECK_CODE(aCrv->Init(*nurbs_curve_sf));
    Naive_ROSTER_ADD(aCrv, *nurbs_curve);
    return Naive_Code_ok;
  }

  return Naive_Code_bad_dimension;
}

Naive_Code_t Naive_NurbsCurve_raise_degree(Naive_NurbsCurve_t nurbs_curve,
                                           int increment) {
  Naive_ROSTER_ASK(Naive_Object, nurbs_curve, Obj);

  if (Obj->GetClassType()->IsSubClass(Naive_CLASS(Naive_NurbsCurve))) {
    Handle_Naive_NurbsCurve H = Handle_Naive_NurbsCurve::DownCast(Obj);
    return H->RaiseDegree(increment);
  } else if (Obj->GetClassType()->IsSubClass(Naive_CLASS(Naive_NurbsCurve2d))) {
    Handle_Naive_NurbsCurve2d H = Handle_Naive_NurbsCurve2d::DownCast(Obj);
    return H->RaiseDegree(increment);
  } else {
    return Naive_Code_invalid_tag;
  }
}

Naive_Code_t Naive_NurbsCurve_remove_knot(Naive_NurbsCurve_t nurbs_curve,
                                          int index, int mult) {
  Naive_ROSTER_ASK(Naive_Object, nurbs_curve, Obj);

  if (Obj->GetClassType()->IsSubClass(Naive_CLASS(Naive_NurbsCurve))) {
    Handle_Naive_NurbsCurve H = Handle_Naive_NurbsCurve::DownCast(Obj);
    return H->RemoveKnot(index, mult);
  } else if (Obj->GetClassType()->IsSubClass(Naive_CLASS(Naive_NurbsCurve2d))) {
    Handle_Naive_NurbsCurve2d H = Handle_Naive_NurbsCurve2d::DownCast(Obj);
    return H->RemoveKnot(index, mult);
  } else {
    return Naive_Code_invalid_tag;
  }
}
