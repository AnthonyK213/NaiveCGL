#include "../NurbsCurve.h"

Naive_NAMESPACE_BEGIN(geometry2d);

template <typename CPs_, typename Knots_, typename Mults_>
Naive_Code NurbsCurve::update(CPs_ &&theCPs, Knots_ &&theKnots,
                              Mults_ &&theMults, const Naive_Integer theDegree,
                              const Naive_Bool thePeriodic) {
  Naive_Code aCode = Naive_Code_ok;

  aCode = math::Nurbs::CheckParam(theCPs.size(), theKnots, theMults, theDegree,
                                  myPeriodic, myFlatKnots);

  if (aCode != Naive_Code_ok)
    return aCode;

  for (Naive_Integer i = 0; i < theCPs.size(); ++i) {
    if (!math::Util::IsValidReal(theCPs[i].z()))
      return Naive_Code_invalid_value;

    if (theCPs[i].z() <= 0)
      return Naive_Code_weight_le_0;
  }

  for (Naive_Integer i = 1; i < theCPs.size(); ++i) {
    if (!math::Util::EpsilonEquals(theCPs[i].z(), theCPs[0].z())) {
      myRational = Naive_True;
      break;
    }
  }

  myCPs = ::std::forward<CPs_>(theCPs);
  myKnots = ::std::forward<Knots_>(theKnots);
  myMults = ::std::forward<Mults_>(theMults);
  myDegree = theDegree;
  myPeriodic = thePeriodic;

  return aCode;
}

Naive_NAMESPACE_END(geometry2d);
