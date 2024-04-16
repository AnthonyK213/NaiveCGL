#include "../NurbsCurve.h"

Naive_NAMESPACE_BEGIN(geometry);

template <typename P, typename R, typename I>
Naive_Bool NurbsCurve::update(P &&thePoles, R &&theWeights, R &&theKnots,
                              I &&theMults, const Naive_Integer theDegree) {
  if (!math::Nurbs::CheckParam(thePoles.size(), theWeights.size(), theKnots,
                               theMults, theDegree, myPeriodic, myFlatKnots,
                               mySpanIdx))
    return false;

  for (Naive_Integer i = 1; i < theWeights.size(); ++i) {
    if (!math::Util::EpsilonEquals(theWeights[i], theWeights[0])) {
      myRational = true;
      break;
    }
  }

  myPoles = ::std::forward<P>(thePoles);
  myWeights = ::std::forward<R>(theWeights);
  myKnots = ::std::forward<R>(theKnots);
  myMults = ::std::forward<I>(theMults);
  myDegree = theDegree;

  return true;
}

Naive_NAMESPACE_END(geometry);
