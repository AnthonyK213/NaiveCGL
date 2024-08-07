#include <naivecgl/Common/Roster.h>
#include <naivecgl/Geometry/NurbsCurve.h>

#include "Interface_NaiveCGL_c.h"

Naive_Code_t Naive_NurbsCurve_ask_degree(Naive_NurbsCurve_t nurbs_curve,
                                         int *const degree) {
  if (!degree)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_NurbsCurve, nurbs_curve, H);
  *degree = H->Degree();
  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_knots(Naive_NurbsCurve_t nurbs_curve,
                                        int *const n_knots,
                                        double **const knots) {
  if (!n_knots || !knots)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbKnots = H->NbKnots();
  if (nbKnots <= 0)
    return Naive_Code_invalid_object;

  *n_knots = nbKnots;

  const Naive_RealList1 &aKnots = H->Knots();
  Naive_ALLOC_ARRAY(double, nbKnots, knots);
  ::std::copy(aKnots.cbegin(), aKnots.cend(), *knots);

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_mults(Naive_NurbsCurve_t nurbs_curve,
                                        int *const n_mults, int **const mults) {
  if (!n_mults || !mults)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbMults = H->NbKnots();
  if (nbMults <= 0)
    return Naive_Code_invalid_object;

  *n_mults = nbMults;

  const Naive_IntegerList1 &aMults = H->Multiplicities();
  Naive_ALLOC_ARRAY(int, nbMults, mults);
  ::std::copy(aMults.cbegin(), aMults.cend(), *mults);

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_poles(Naive_NurbsCurve_t nurbs_curve,
                                        int *const n_poles,
                                        Naive_Pnt3d_t **const poles) {
  if (!n_poles || !poles)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbPoles = H->NbPoles();
  if (nbPoles <= 0)
    return Naive_Code_invalid_object;

  *n_poles = nbPoles;

  const Naive_Pnt3dList1 &aPoles = H->Poles();
  Naive_ALLOC_ARRAY(Naive_Pnt3d_t, nbPoles, poles);
  for (Naive_Integer i = 0; i < nbPoles; ++i) {
    aPoles[i].Dump((*poles)[i]);
  }

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_ask_weights(Naive_NurbsCurve_t nurbs_curve,
                                          int *const n_weights,
                                          double **const weights) {
  if (!n_weights || !weights)
    return Naive_Code_null_arg_address;

  Naive_ROSTER_ASK(Naive_NurbsCurve, nurbs_curve, H);
  Naive_Integer nbWeights = H->NbPoles();
  if (nbWeights <= 0)
    return Naive_Code_invalid_object;

  *n_weights = nbWeights;

  const Naive_RealList1 &aWeights = H->Weights();
  Naive_ALLOC_ARRAY(double, nbWeights, weights);
  ::std::copy(aWeights.cbegin(), aWeights.cend(), *weights);

  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_create(int n_poles, const Naive_Pnt3d_t *poles,
                                     int n_weights, const double *weights,
                                     int n_knots, const double *knots,
                                     int n_mults, const int *mults, int degree,
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
  Naive_CHECK_CODE(aCrv->Init(aPoles, aWeights, aKnots, aMults, degree));

  Naive_ROSTER_ADD(aCrv, *nurbs_curve);
  return Naive_Code_ok;
}

Naive_Code_t Naive_NurbsCurve_increase_degree(Naive_NurbsCurve_t nurbs_curve,
                                              int degree) {
  Naive_ROSTER_ASK(Naive_NurbsCurve, nurbs_curve, H);
  return H->IncreaseDegree(degree);
}

Naive_Code_t
Naive_NurbsCurve_increase_multiplicity(Naive_NurbsCurve_t nurbs_curve,
                                       int index, int mult) {
  Naive_ROSTER_ASK(Naive_NurbsCurve, nurbs_curve, H);
  return H->IncreaseMultiplicity(index, mult);
}

Naive_Code_t Naive_NurbsCurve_insert_knot(Naive_NurbsCurve_t nurbs_curve,
                                          double t, int mult) {
  Naive_ROSTER_ASK(Naive_NurbsCurve, nurbs_curve, H);
  return H->InsertKnot(t, mult);
}

Naive_Code_t Naive_NurbsCurve_remove_knot(Naive_NurbsCurve_t nurbs_curve,
                                          int index, int mult) {
  Naive_ROSTER_ASK(Naive_NurbsCurve, nurbs_curve, H);
  return H->RemoveKnot(index, mult);
}
