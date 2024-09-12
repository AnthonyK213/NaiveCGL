#include "../NurbsSurface.h"

Naive_NAMESPACE_BEGIN(geometry);

template <typename CPs2_, typename Knots_, typename Mults_>
Naive_Code NurbsSurface::update(CPs2_ &&theCPs, Knots_ &&theUKnots,
                                Knots_ &&theVKnots, Mults_ &&theUMults,
                                Mults_ &&theVMults,
                                const Naive_Integer theUDegree,
                                const Naive_Integer theVDegree,
                                const Naive_Bool theUPeriodic,
                                const Naive_Bool theVPeriodic) {
  if (theUDegree < 1 || theVDegree < 1)
    return Naive_Code_value_out_of_range;

  Naive_Code aCode = Naive_Code_ok;

  Naive_Integer aPU, aPV;
  aCode = math::Util::List2CheckBound(theCPs, aPU, aPV);
  if (aCode != Naive_Code_ok)
    return aCode;

  if (aPU < 2 || aPV < 2)
    return Naive_Code_value_out_of_range;

  aCode = math::Nurbs::CheckParam(aPU, theUKnots, theUMults, theUDegree,
                                  myUPeriodic, myUFlatKnots);
  if (aCode != Naive_Code_ok)
    return aCode;

  aCode = math::Nurbs::CheckParam(aPV, theVKnots, theVMults, theVDegree,
                                  myVPeriodic, myVFlatKnots);
  if (aCode != Naive_Code_ok)
    return aCode;

  for (Naive_Integer i = 0; i < aPU; ++i) {
    for (Naive_Integer j = 1; j < aPV; ++j) {
      if (!math::Util::IsValidReal(theCPs[i][j].w()))
        return Naive_Code_invalid_value;

      if (theCPs[i][j].w() <= math::Precision::Zero())
        return Naive_Code_weight_le_0;
    }
  }

  for (Naive_Integer j = 0; j < aPV; ++j) {
    for (Naive_Integer i = 1; i < aPU; ++i) {
      if (!math::Util::EpsilonEquals(theCPs[i][j].w(), theCPs[0][j].w())) {
        myURational = Naive_True;
        break;
      }
    }
  }

  for (Naive_Integer i = 0; i < aPU; ++i) {
    for (Naive_Integer j = 1; j < aPV; ++j) {
      if (!math::Util::EpsilonEquals(theCPs[i][j].w(), theCPs[i][0].w())) {
        myVRational = Naive_True;
        break;
      }
    }
  }

  myCPs = ::std::forward<CPs2_>(theCPs);
  myUKnots = ::std::forward<Knots_>(theUKnots);
  myVKnots = ::std::forward<Knots_>(theVKnots);
  myUMults = ::std::forward<Mults_>(theUMults);
  myVMults = ::std::forward<Mults_>(theVMults);
  myUDegree = theUDegree;
  myVDegree = theVDegree;
  // myUPeriodic = theUPeriodic;
  // myVPeriodic = theVPeriodic;

  return Naive_Code_ok;
}

Naive_NAMESPACE_END(geometry);
