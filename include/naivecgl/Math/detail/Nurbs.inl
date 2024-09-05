#include "../Nurbs.h"

Naive_NAMESPACE_BEGIN(math);

template <typename OutTy_, Naive_Integer Dim_>
static Naive_Code
Nurbs::EvaluateCurve(const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
                     const Naive_RealList1 &theFlatKnots,
                     const Naive_RealList1 &theKnots,
                     const Naive_IntegerList1 &theMults, const Naive_Real theT,
                     const Naive_Integer theN, Naive_List1<OutTy_> theResult) {
  if (theN < 0)
    return Naive_Code_value_out_of_range;

  Naive_Integer iSpan = math::Nurbs::FindFlatSpan(theKnots, theMults, theT);
  if (iSpan < 0)
    return Naive_Code_value_out_of_range;

  theResult.resize(theN + 1, Naive_Vec3d::Unset());

  return Naive_Code_ok;
}

template <Naive_Integer Dim_>
static Naive_VNd<Dim_ + 1>
Nurbs::PoleAfterInsertKnot(const Naive_List1<Naive_VNd<Dim_ + 1>> &theCPs,
                           const Naive_RealList1 &theFlatKnots,
                           const Naive_Integer theDegree, const Naive_Real theT,
                           const Naive_Integer theK, const Naive_Integer theS,
                           const Naive_Integer theI, const Naive_Integer theM) {
  if (theM == 0)
    return thePoles[theI].HomoCoord() * theWeights[theI];

  if (theI <= theK - theDegree + theM - 1)
    return PoleAfterInsertKnot<Dim_, T>(theCPs, theFlatKnots, theDegree, theT,
                                        theK, theS, theI, theM - 1);

  if (theI >= theK - theS + 1)
    return PoleAfterInsertKnot<Dim_, T>(theCPs, theFlatKnots, theDegree, theT,
                                        theK, theS, theI - 1, theM - 1);

  auto q1 = PoleAfterInsertKnot<Dim_, T>(theCPs, theFlatKnots, theDegree, theT,
                                         theK, theS, theI, theM - 1);
  auto q2 = PoleAfterInsertKnot<Dim_, T>(theCPs, theFlatKnots, theDegree, theT,
                                         theK, theS, theI - 1, theM - 1);
  Naive_Real a =
      (theT - theFlatKnots[theI]) /
      (theFlatKnots[theI + theDegree - theM + 1] - theFlatKnots[theI]);

  return a * q1 + (1. - a) * q2;
}

Naive_NAMESPACE_END(math);
