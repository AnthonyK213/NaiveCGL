#include "../NurbsCurve.h"

Naive_NAMESPACE_BEGIN(geometry2d);

template <typename P, typename Rw, typename Rk, typename I>
Naive_Code NurbsCurve::update(P &&thePoles, Rw &&theWeights, Rk &&theKnots,
                              I &&theMults, const Naive_Integer theDegree) {
  Naive_Code aCode = Naive_Code_ok;

  // aCode = math::Nurbs::CheckParam(thePoles.size(), theWeights.size(),
  // theKnots,
  //                                 theMults, theDegree, myPeriodic,
  //                                 myFlatKnots, mySpanIdx);
  // if (aCode != Naive_Code_ok)
  //   return aCode;

  // for (Naive_Integer i = 0; i < thePoles.size(); ++i) {
  //   if (!thePoles[i].IsValid())
  //     return Naive_Code_invalid_value;

  //   if (!math::Util::IsValidReal(theWeights[i]))
  //     return Naive_Code_invalid_value;

  //   if (theWeights[i] <= 0)
  //     return Naive_Code_weight_le_0;
  // }

  // for (Naive_Integer i = 1; i < theWeights.size(); ++i) {
  //   if (!math::Util::EpsilonEquals(theWeights[i], theWeights[0])) {
  //     myRational = Naive_True;
  //     break;
  //   }
  // }

  // myPoles = ::std::forward<P>(thePoles);
  // myWeights = ::std::forward<Rw>(theWeights);
  // myKnots = ::std::forward<Rk>(theKnots);
  // myMults = ::std::forward<I>(theMults);
  // myDegree = theDegree;

  return aCode;
}

Naive_NAMESPACE_END(geometry2d);
