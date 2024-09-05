﻿#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Nurbs.h>
#include <naivecgl/Math/Polynomial.h>
#include <naivecgl/Math/Util.h>

#include <numeric>

Naive_NAMESPACE_BEGIN(math);

Naive_Code Nurbs::CheckParam(const Naive_Integer nbCPs,
                             const Naive_RealList1 &theKnots,
                             const Naive_IntegerList1 &theMults,
                             const Naive_Integer theDegree,
                             Naive_Bool &myPeriodic,
                             Naive_RealList1 &theFlatKnots) {
  /* 1 <= Degree <= 9 */
  if (theDegree < 1 || theDegree > 9)
    return Naive_Code_value_out_of_range;

  if (nbCPs < 2)
    return Naive_Code_insufficient_points;

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

  Naive_Integer nbFlatKnots =
      ::std::accumulate(theMults.cbegin(), theMults.cend(), 0);

  if (nbCPs + theDegree + 1 == nbFlatKnots)
    myPeriodic = Naive_False;
  else if (nbCPs == nbFlatKnots)
    /* TODO: What is periodic? */
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
                                  const Naive_IntegerList1 &theMults,
                                  const Naive_Real theT) {
  Naive_Integer k = FindSpan(theKnots, theT);
  if (k < 0)
    return -1;
  return ::std::accumulate(&theMults[0], &theMults[k + 1], -1);
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

class BasisFnEvalCache {
public:
  BasisFnEvalCache(Naive_Integer theI0, Naive_Integer theI1, Naive_Integer theP,
                   Naive_Integer theSpan)
      : myData(), myLower(theI0) {
    Naive_Integer nbI = theI1 - theI0 + theP + 1;
    myData.resize(nbI);

    for (Naive_Integer i = 0; i < nbI; ++i) {
      myData[i].resize(theP + 1, math::Constant::UnsetReal());
      myData[i][0] = 0.;
    }

    SetValue(theSpan, 0, 1.);
  }

  Naive_Real Value(Naive_Integer theI, Naive_Integer theP) const {
    return myData[theI - myLower][theP];
  }

  void SetValue(Naive_Integer theI, Naive_Integer theP, Naive_Real theV) {
    myData[theI - myLower][theP] = theV;
  }

private:
  Naive_RealList2 myData;
  Naive_Integer myLower;
};

static Naive_Real basisFnEval(const Naive_RealList1 &theFlatKnots,
                              Naive_Integer theI, Naive_Integer theP,
                              Naive_Real theT, BasisFnEvalCache &theCache) {
  Naive_Real vF = theCache.Value(theI, theP - 1);
  if (vF < 0.0) {
    vF = basisFnEval(theFlatKnots, theI, theP - 1, theT, theCache);
    theCache.SetValue(theI, theP - 1, vF);
  }

  Naive_Real vG = theCache.Value(theI + 1, theP - 1);
  if (vG < 0.0) {
    vG = basisFnEval(theFlatKnots, theI + 1, theP - 1, theT, theCache);
    theCache.SetValue(theI + 1, theP - 1, vG);
  }

  Naive_Real aF0 = theFlatKnots[theI + theP] - theFlatKnots[theI];
  Naive_Real aG0 = theFlatKnots[theI + theP + 1] - theFlatKnots[theI + 1];

  Naive_Real aF =
      Util::EpsilonEquals(aF0, 0.) ? 0. : ((theT - theFlatKnots[theI]) / aF0);
  Naive_Real aG = Util::EpsilonEquals(aG0, 0.)
                      ? 0.
                      : ((theFlatKnots[theI + theP + 1] - theT) / aG0);

  return aF * vF + aG * vG;
}

Naive_Real Nurbs::BasisFnEval(const Naive_RealList1 &theFlatKnots,
                              const Naive_RealList1 &theKnots,
                              const Naive_IntegerList1 &theMults,
                              Naive_Integer theI, Naive_Integer theP,
                              Naive_Real theT) {
  Naive_Integer aSpan = FindFlatSpan(theKnots, theMults, theT);
  BasisFnEvalCache aCache(theI, theI, theP, aSpan);
  return basisFnEval(theFlatKnots, theI, theP, theT, aCache);
}

Naive_RealList1 Nurbs::BasisFnEvalAll(const Naive_RealList1 &theFlatKnots,
                                      const Naive_RealList1 &theKnots,
                                      const Naive_IntegerList1 &theMults,
                                      Naive_Integer theN, Naive_Integer theD,
                                      Naive_Real theT) {
  Naive_Integer aSpan = FindFlatSpan(theKnots, theMults, theT);
  BasisFnEvalCache aCache(0, theN, theD, aSpan);
  Naive_RealList1 aResult(theN, 0.);

  for (Naive_Integer i = 0; i < theN; ++i) {
    aResult[i] = basisFnEval(theFlatKnots, i, theD, theT, aCache);
  }

  return aResult;
}

Naive_RealList2 Nurbs::BasisFnDerEvalAll(const Naive_RealList1 &theFlatKnots,
                                         const Naive_RealList1 &theKnots,
                                         const Naive_IntegerList1 &theMults,
                                         Naive_Integer theN, Naive_Integer theD,
                                         Naive_Real theT,
                                         Naive_Integer theDer) {
  Naive_RealList2 aResult(theDer + 1, Naive_RealList1(theN, 0.));

  for (Naive_Integer d = 0; d <= theDer; ++d) {
    for (Naive_Integer i = 0; i < theN; ++i) {
      // Polynomial aPol = BasisFn(theFlatKnots, theKnots, theMults, i, theD,
      // theT); aResult[d][i] =
    }
  }

  return aResult;
}

Naive_NAMESPACE_END(math);
