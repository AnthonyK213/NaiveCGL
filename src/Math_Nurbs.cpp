#include <naivecgl/Math/Nurbs.h>

Naive_NAMESPACE_BEGIN(math);

Naive_Bool
Nurbs::CheckParam(const Naive_Integer nbPoles, const Naive_RealList &theKnots,
                  const Naive_IntegerList &theMults,
                  const Naive_Integer theDegree, Naive_Bool &myPeriodic,
                  Naive_RealList &theFlatKnots, Naive_IntegerList &theSpanIdx) {
  if (nbPoles < 2 || theDegree < 1)
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
  for (Naive_Integer i = 0; i < theKnots.size(); ++i) {
    for (Naive_Integer j = 0; j < theMults[i]; ++j) {
      theFlatKnots.push_back(theKnots[i]);
    }
  }

  return true;
}

Naive_NAMESPACE_END(math);
