#include "../Nurbs.h"

Naive_NAMESPACE_BEGIN(math);

template <int Dim, typename T>
Naive_EXPORT ::Eigen::Matrix<Naive_Real, Dim + 1, 1> Nurbs::PoleAfterInsertKnot(
    const Naive_List1<T> &thePoles, const Naive_RealList1 &theWeights,
    const Naive_RealList1 &theFlatKnots, const Naive_Integer theDegree,
    const Naive_Real theT, const Naive_Integer theK, const Naive_Integer theS,
    const Naive_Integer theI, const Naive_Integer theM) {
  if (theM == 0)
    return thePoles[theI].HomoCoord() * theWeights[theI];

  if (theI <= theK - theDegree + theM - 1)
    return PoleAfterInsertKnot<Dim, T>(thePoles, theWeights, theFlatKnots,
                                       theDegree, theT, theK, theS, theI,
                                       theM - 1);

  if (theI >= theK - theS + 1)
    return PoleAfterInsertKnot<Dim, T>(thePoles, theWeights, theFlatKnots,
                                       theDegree, theT, theK, theS, theI - 1,
                                       theM - 1);

  auto q1 =
      PoleAfterInsertKnot<Dim, T>(thePoles, theWeights, theFlatKnots, theDegree,
                                  theT, theK, theS, theI, theM - 1);
  auto q2 =
      PoleAfterInsertKnot<Dim, T>(thePoles, theWeights, theFlatKnots, theDegree,
                                  theT, theK, theS, theI - 1, theM - 1);
  Naive_Real a =
      (theT - theFlatKnots[theI]) /
      (theFlatKnots[theI + theDegree - theM + 1] - theFlatKnots[theI]);

  return a * q1 + (1. - a) * q2;
}

Naive_NAMESPACE_END(math);
