#include <naivecgl/Geometry/NurbsCurve.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_NurbsCurve_new(const int n_poles,
                                  const Naive_Point3d_t *poles,
                                  const int n_weights, const double *weights,
                                  const int n_knots, const double *knots,
                                  const int n_mults, const int *mults,
                                  const int degree,
                                  Naive_NurbsCurve_t *const nurbs_curve) {
  if (!poles || !weights || !knots || !mults || !nurbs_curve)
    return Naive_Code_null_arg_address;

  if (n_poles < 2 || n_weights < 2 || n_knots < 2 || n_mults < 2 || degree < 1)
    return Naive_Code_value_out_of_range;

  Naive_Pnt3dList1 aPoles(poles, poles + n_poles);
  Naive_RealList1 aWeights(weights, weights + n_weights);
  Naive_RealList1 aKnots(knots, knots + n_knots);
  Naive_IntegerList1 aMults(mults, mults + n_mults);

  Handle_Naive_NurbsCurve aCrv = new Naive_NurbsCurve;
  Naive_Code aCode = aCrv->Init(aPoles, aWeights, aKnots, aMults, degree);
  if (aCode)
    return aCode;

  aCrv->IncrementRefCounter();
  *nurbs_curve = aCrv.get();
  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_degree(const Naive_NurbsCurve_t nurbs_curve,
                                         int *const degree) {
  if (!degree)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, nurbs_curve, H);
  *degree = H->Degree();
  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_poles(const Naive_NurbsCurve_t nurbs_curve,
                                        int *const n_poles,
                                        Naive_Point3d_t *const poles) {
  if (!n_poles)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbPoles = H->NbPoles();
  if (nbPoles <= 0)
    return Naive_Code_invalid_handle;

  *n_poles = nbPoles;

  if (poles) {
    const Naive_Pnt3dList1 &aPoles = H->Poles();
    for (Naive_Integer i = 0; i < nbPoles; ++i) {
      aPoles[i].Dump(poles[i]);
    }
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_weights(const Naive_NurbsCurve_t nurbs_curve,
                                          int *const n_weights,
                                          double *const weights) {
  if (!n_weights)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbWeights = H->NbPoles();
  if (nbWeights <= 0)
    return Naive_Code_invalid_handle;

  *n_weights = nbWeights;

  if (weights) {
    const Naive_RealList1 &aWeights = H->Weights();
    ::std::copy(aWeights.cbegin(), aWeights.cend(), weights);
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_knots(const Naive_NurbsCurve_t nurbs_curve,
                                        int *const n_knots,
                                        double *const knots) {
  if (!n_knots)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbKnots = H->NbKnots();
  if (nbKnots <= 0)
    return Naive_Code_invalid_handle;

  *n_knots = nbKnots;

  if (knots) {
    const Naive_RealList1 &aKnots = H->Knots();
    ::std::copy(aKnots.cbegin(), aKnots.cend(), knots);
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_mults(const Naive_NurbsCurve_t nurbs_curve,
                                        int *const n_mults, int *const mults) {
  if (!n_mults)
    return Naive_Code_null_arg_address;

  Naive_H_CAST_AND_CHECK(const Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbMults = H->NbKnots();
  if (nbMults <= 0)
    return Naive_Code_invalid_handle;

  *n_mults = nbMults;

  if (mults) {
    const Naive_IntegerList1 &aMults = H->Multiplicities();
    ::std::copy(aMults.cbegin(), aMults.cend(), mults);
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_increase_degree(Naive_NurbsCurve_t nurbs_curve,
                                              const int degree) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, nurbs_curve, H);
  return H->IncreaseDegree(degree);
}

Naive_Code_t
Naive_NurbsCurve_increase_multiplicity(Naive_NurbsCurve_t nurbs_curve,
                                       const int index, const int mult) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, nurbs_curve, H);
  return H->IncreaseMultiplicity(index, mult);
}

Naive_Code_t Naive_NurbsCurve_insert_knot(Naive_NurbsCurve_t nurbs_curve,
                                          const double t, const int mult) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, nurbs_curve, H);
  return H->InsertKnot(t, mult);
}

Naive_Code_t Naive_NurbsCurve_remove_knot(Naive_NurbsCurve_t nurbs_curve,
                                          const int index, const int mult) {
  Naive_H_CAST_AND_CHECK(Naive_NurbsCurve, nurbs_curve, H);
  return H->RemoveKnot(index, mult);
}
