#include "../NurbsSurface.h"

Naive_NAMESPACE_BEGIN(geometry);

template <typename P2, typename R2, typename R, typename I>
Naive_Bool NurbsSurface::update(P2 &&thePoles, R2 &&theWeights, R &&theUKnots,
                                R &&theVKnots, I &&theUMults, I &&theVMults,
                                const Naive_Integer theUDegree,
                                const Naive_Integer theVDegree) {
  if (theUDegree < 1 || theVDegree < 1)
    return false;

  Naive_Integer aPU, aPV, aWU, aWV;
  if (!math::Util::List2CheckBound(thePoles, aPU, aPV) ||
      !math::Util::List2CheckBound(theWeights, aWU, aWV))
    return false;

  if (aPU < 2 || aPV < 2)
    return false;

  if (aPU != aWU || aPV != aWV)
    return false;

  if (!math::Nurbs::CheckParam(aPU, aWU, theUKnots, theUMults, theUDegree,
                               myUPeriodic, myUFlatKnots, myUSpanIdx))
    return false;

  if (!math::Nurbs::CheckParam(aPV, aWV, theVKnots, theVMults, theVDegree,
                               myVPeriodic, myVFlatKnots, myVSpanIdx))
    return false;

  for (Naive_Integer j = 0; j < aWV; ++j) {
    for (Naive_Integer i = 1; i < aWU; ++i) {
      if (!math::Util::EpsilonEquals(theWeights[i][j], theWeights[0][j])) {
        myURational = true;
        break;
      }
    }
  }

  for (Naive_Integer i = 0; i < aWU; ++i) {
    for (Naive_Integer j = 1; j < aWV; ++j) {
      if (!math::Util::EpsilonEquals(theWeights[i][j], theWeights[i][0])) {
        myVRational = true;
        break;
      }
    }
  }

  myPoles = ::std::forward<P2>(thePoles);
  myWeights = ::std::forward<R2>(theWeights);
  myUKnots = ::std::forward<R>(theUKnots);
  myVKnots = ::std::forward<R>(theVKnots);
  myUMults = ::std::forward<I>(theUMults);
  myVMults = ::std::forward<I>(theVMults);
  myUDegree = theUDegree;
  myVDegree = theVDegree;

  return true;
}

Naive_NAMESPACE_END(geometry);
