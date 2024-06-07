#include "../NurbsCurve.h"

Naive_NAMESPACE_BEGIN(geometry);

template <typename P, typename Rw, typename Rk, typename I>
Naive_Bool NurbsCurve::update(P &&thePoles, Rw &&theWeights, Rk &&theKnots,
                              I &&theMults, const Naive_Integer theDegree) {
  if (!math::Nurbs::CheckParam(thePoles.size(), theWeights.size(), theKnots,
                               theMults, theDegree, myPeriodic, myFlatKnots,
                               mySpanIdx))
    return Naive_False;

  for (Naive_Integer i = 1; i < theWeights.size(); ++i) {
    if (!math::Util::EpsilonEquals(theWeights[i], theWeights[0])) {
      myRational = Naive_True;
      break;
    }
  }

  myPoles = ::std::forward<P>(thePoles);
  myWeights = ::std::forward<Rw>(theWeights);
  myKnots = ::std::forward<Rk>(theKnots);
  myMults = ::std::forward<I>(theMults);
  myDegree = theDegree;

  return Naive_True;
}

Naive_NAMESPACE_END(geometry);
