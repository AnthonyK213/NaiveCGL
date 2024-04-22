#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Math/Nurbs.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(math);

Naive_Bool
Nurbs::CheckParam(const Naive_Integer nbPoles, const Naive_Integer nbWeights,
                  const Naive_RealList &theKnots,
                  const Naive_IntegerList &theMults,
                  const Naive_Integer theDegree, Naive_Bool &myPeriodic,
                  Naive_RealList &theFlatKnots, Naive_IntegerList &theSpanIdx) {
  if (nbPoles < 2 || nbPoles != nbWeights || theDegree < 1)
    return false;

  if (theKnots.size() < 2)
    return false;

  if (theKnots.size() != theMults.size())
    return false;

  for (Naive_Integer i = 0; i < theMults.size(); ++i) {
    if (theMults[i] < 1)
      return false;

    if (i != 0 && i != theMults.size() - 1) {
      if (theMults[i] > theDegree)
        return false;
    } else if (theMults[i] > theDegree + 1) {
      return false;
    }
  }

  for (Naive_Integer i = 1; i < theKnots.size(); ++i) {
    if (theKnots[i] <= theKnots[i - 1])
      return false;
  }

  theSpanIdx.reserve(theMults.size() - 1);
  theSpanIdx.clear();
  Naive_Integer nbFlatKnots = theMults[0];
  for (Naive_Integer i = 1; i < theMults.size(); ++i) {
    theSpanIdx.push_back(nbFlatKnots);
    nbFlatKnots += theMults[i];
  }

  if (nbPoles + theDegree + 1 == nbFlatKnots)
    myPeriodic = false;
  else if (nbPoles == nbFlatKnots)
    // TODO: What is periodic?
    myPeriodic = true;
  else
    return false;

  theFlatKnots.reserve(nbFlatKnots);
  theFlatKnots.clear();
  for (Naive_Integer i = 0; i < theKnots.size(); ++i) {
    for (Naive_Integer j = 0; j < theMults[i]; ++j) {
      theFlatKnots.push_back(theKnots[i]);
    }
  }

  return true;
}

Naive_Integer Nurbs::FindSpan(const Naive_RealList &theKnots,
                              const Naive_Real theT) {
  if (theKnots.size() < 2)
    return -1;

  Naive_Real aF = theKnots[0];
  Naive_Real aL = theKnots[theKnots.size() - 1];
  if (theT < aF || theT > aL)
    return -1;

  Naive_Integer m = static_cast<Naive_Integer>(theKnots.size()) - 1;
  Naive_Integer k;
  if (theT == aL) {
    /* The last knot belongs to the last span. */
    return m - 1;
  } else {
    Naive_Integer lower = 0;
    Naive_Integer upper = m;
    while (upper - lower > 1) {
      Naive_Integer mid = (lower + upper) >> 1;
      if (theT < theKnots[mid])
        upper = mid;
      else
        lower = mid;
    }
    return lower;
  }
}

Naive_Integer Nurbs::FindFlatSpan(const Naive_RealList &theKnots,
                                  const Naive_IntegerList &theSpanIdx,
                                  const Naive_Real theT) {
  // if (theSpanIdx.size() != theKnots.size() - 1)
  //   return -1;

  Naive_Integer k = FindSpan(theKnots, theT);
  if (k < 0)
    return -1;

  return theSpanIdx[k] - 1;
}

Polynomial Nurbs::BasisFn(const Naive_RealList &theFlatKnots,
                          Naive_Integer theI, Naive_Integer theP,
                          Naive_Integer theSpan) {
  if (theP == 0)
    return theSpan == theI ? Polynomial::Identity() : Polynomial::Zero();

  Naive_Real aF0 = theFlatKnots[theI + theP] - theFlatKnots[theI];
  Naive_Real aG0 = theFlatKnots[theI + theP + 1] - theFlatKnots[theI + 1];
  Polynomial aF = Util::EpsilonEquals(aF0, 0.)
                      ? Polynomial::Zero()
                      : Polynomial({-theFlatKnots[theI], 1.}).Divided(aF0);
  Polynomial aG =
      Util::EpsilonEquals(aG0, 0.)
          ? Polynomial::Zero()
          : Polynomial({theFlatKnots[theI + theP + 1], -1.}).Divided(aG0);

  aF.Multiply(BasisFn(theFlatKnots, theI, theP - 1, theSpan));
  aG.Multiply(BasisFn(theFlatKnots, theI + 1, theP - 1, theSpan));
  aF.Add(aG);

  return aF;
}

Naive_XYZW Nurbs::PoleAfterInsertKnot(
    const Naive_Point3dList &thePoles, const Naive_RealList &theWeights,
    const Naive_RealList &theFlatKnots, const Naive_Integer theDegree,
    const Naive_Real theT, const Naive_Integer theK, const Naive_Integer theS,
    const Naive_Integer theI, const Naive_Integer theM) {
  if (theM == 0)
    return Naive_XYZW{thePoles[theI].X(), thePoles[theI].Y(),
                      thePoles[theI].Z(), 1.0} *
           theWeights[theI];

  if (theI <= theK - theDegree + theM - 1)
    return PoleAfterInsertKnot(thePoles, theWeights, theFlatKnots, theDegree,
                               theT, theK, theS, theI, theM - 1);

  if (theI >= theK - theS + 1)
    return PoleAfterInsertKnot(thePoles, theWeights, theFlatKnots, theDegree,
                               theT, theK, theS, theI - 1, theM - 1);

  Naive_XYZW q1 =
      PoleAfterInsertKnot(thePoles, theWeights, theFlatKnots, theDegree, theT,
                          theK, theS, theI, theM - 1);
  Naive_XYZW q2 =
      PoleAfterInsertKnot(thePoles, theWeights, theFlatKnots, theDegree, theT,
                          theK, theS, theI - 1, theM - 1);
  Naive_Real a =
      (theT - theFlatKnots[theI]) /
      (theFlatKnots[theI + theDegree - theM + 1] - theFlatKnots[theI]);
  return a * q1 + (1. - a) * q2;
}

Naive_NAMESPACE_END(math);
