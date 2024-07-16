#include <naivecgl/Math/Nurbs.h>
#include <naivecgl/Math/Polynomial.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(math);

Naive_Code Nurbs::CheckParam(
    const Naive_Integer nbPoles, const Naive_Integer nbWeights,
    const Naive_RealList1 &theKnots, const Naive_IntegerList1 &theMults,
    const Naive_Integer theDegree, Naive_Bool &myPeriodic,
    Naive_RealList1 &theFlatKnots, Naive_IntegerList1 &theSpanIdx) {
  /* 1 <= Degree <= 9 */
  if (theDegree < 1 || theDegree > 9)
    return Naive_Code_value_out_of_range;

  if (nbPoles < 2)
    return Naive_Code_insufficient_points;

  if (nbPoles != nbWeights)
    return Naive_Code_poles_weights_not_match;

  if (theKnots.size() < 2)
    return Naive_Code_insufficient_knots;

  if (theKnots.size() != theMults.size())
    return Naive_Code_knots_mults_not_match;

  for (Naive_Integer i = 0; i < theMults.size(); ++i) {
    if (!Util::IsValidReal(theKnots[i]))
      return Naive_Code_invalid_value;

    /* 1 <= Mults <= Degree */
    if (theMults[i] < 1)
      return Naive_Code_invalid_mults;

    if (i != 0 && i != theMults.size() - 1) {
      if (theMults[i] > theDegree)
        return Naive_Code_invalid_mults;
    } else if (theMults[i] > theDegree + 1) {
      return Naive_Code_invalid_mults;
    }
  }

  /* The knots must be strictly increasing. */
  for (Naive_Integer i = 1; i < theKnots.size(); ++i) {
    if (theKnots[i] <= theKnots[i - 1])
      return Naive_Code_bad_knots;
  }

  theSpanIdx.reserve(theMults.size() - 1);
  theSpanIdx.clear();
  Naive_Integer nbFlatKnots = theMults[0];
  for (Naive_Integer i = 1; i < theMults.size(); ++i) {
    theSpanIdx.push_back(nbFlatKnots);
    nbFlatKnots += theMults[i];
  }

  if (nbPoles + theDegree + 1 == nbFlatKnots)
    myPeriodic = Naive_False;
  else if (nbPoles == nbFlatKnots)
    // TODO: What is periodic?
    myPeriodic = Naive_True;
  else
    return Naive_Code_cant_make_nurbs;

  theFlatKnots.reserve(nbFlatKnots);
  theFlatKnots.clear();
  for (Naive_Integer i = 0; i < theKnots.size(); ++i) {
    for (Naive_Integer j = 0; j < theMults[i]; ++j) {
      theFlatKnots.push_back(theKnots[i]);
    }
  }

  return Naive_Code_ok;
}

Naive_Integer Nurbs::FindSpan(const Naive_RealList1 &theKnots,
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

Naive_Integer Nurbs::FindFlatSpan(const Naive_RealList1 &theKnots,
                                  const Naive_IntegerList1 &theSpanIdx,
                                  const Naive_Real theT) {
  // if (theSpanIdx.size() != theKnots.size() - 1)
  //   return -1;

  Naive_Integer k = FindSpan(theKnots, theT);
  if (k < 0)
    return -1;

  return theSpanIdx[k] - 1;
}

Polynomial Nurbs::BasisFn(const Naive_RealList1 &theFlatKnots,
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

Naive_NAMESPACE_END(math);
