#include <naivecgl/Geometry/NurbsSurface.h>
#include <naivecgl/Math/Nurbs.h>

Naive_NAMESPACE_BEGIN(geometry);

template <typename T>
static Naive_Bool checkList2Bound(const Naive_List2<T> &theList2,
                                  Naive_Integer &theU, Naive_Integer &theV) {
  theU = static_cast<Naive_Integer>(theList2.size());
  if (theU == 0) {
    theV = 0;
    return true;
  }

  const Naive_List<T> &aList = theList2[0];
  theV = static_cast<Naive_Integer>(aList.size());
  for (Naive_Integer i = 1; i < theU; ++i) {
    if (theList2[i].size() != theV)
      return false;
  }

  return true;
}

NurbsSurface::NurbsSurface(
    const Naive_Point3dList2 &thePoles, const Naive_RealList2 &theWeights,
    const Naive_RealList &theUKnots, const Naive_RealList &theVKnots,
    const Naive_IntegerList &theUMults, const Naive_IntegerList &theVMults,
    const Naive_Integer theUDegree, const Naive_Integer theVDegree)
    : myURational(false), myVRational(false), myUPeriodic(false),
      myVPeriodic(false), myUDegree(0), myVDegree(0), myUFlatKnots(),
      myVFlatKnots() {
  if (theUDegree < 1 || theVDegree < 1)
    return;

  Naive_Integer aPU, aPV, aWU, aWV;
  if (!checkList2Bound(thePoles, aPU, aPV) ||
      !checkList2Bound(theWeights, aWU, aWV))
    return;

  if (aPU < 2 || aPV < 2)
    return;

  if (aPU != aWU || aPV != aWV)
    return;

  if (!math::Nurbs::CheckParam(aPU, theUKnots, theUMults, theUDegree,
                               myUPeriodic, myUFlatKnots, myUSpanIdx))
    return;

  if (!math::Nurbs::CheckParam(aPV, theVKnots, theVMults, theVDegree,
                               myVPeriodic, myVFlatKnots, myVSpanIdx))
    return;

  // TODO: Rational?

  myPoles = thePoles;
  myWeights = theWeights;
  myUKnots = theUKnots;
  myVKnots = theVKnots;
  myUMults = theUMults;
  myVMults = theVMults;
  myUDegree = theUDegree;
  myVDegree = theVDegree;
}

Naive_Bool NurbsSurface::Bounds(Naive_Real &theU0, Naive_Real &theU1,
                                Naive_Real &theV0, Naive_Real &theV1) const {
  return true;
}

Naive_Point3d NurbsSurface::PointAt(const Naive_Real theU,
                                    const Naive_Real theV) const {
  if (!isValid())
    return Naive_Point3d::Unset();

  Naive_Integer iUSpan = math::Nurbs::FindSpan(myUKnots, myUSpanIdx, theU);
  if (iUSpan < 0)
    return Naive_Point3d::Unset();
  Naive_Integer iVSpan = math::Nurbs::FindSpan(myVKnots, myVSpanIdx, theV);
  if (iVSpan < 0)
    return Naive_Point3d::Unset();

  Naive_XYZ aXYZ(0., 0., 0.);
  Naive_Real aR = 0.;
  Naive_Integer iBegin = (::std::max)(0, iUSpan - myUDegree);
  Naive_Integer jBegin = (::std::max)(0, iVSpan - myVDegree);
  for (Naive_Integer i = iBegin; i <= iUSpan; ++i) {
    for (Naive_Integer j = jBegin; j <= iVSpan; ++j) {
      Naive_Real aN =
          myWeights[i][j] *
          math::Nurbs::BasisFn(myUFlatKnots, i, myUDegree, theU, iUSpan) *
          math::Nurbs::BasisFn(myVFlatKnots, j, myVDegree, theV, iVSpan);
      aXYZ += aN * myPoles[i][j].XYZ();
      aR += aN;
    }
  }

  aXYZ /= aR;
  return aXYZ;
}

Naive_Bool NurbsSurface::isValid() const {
  return myUDegree > 0 && myVDegree > 0;
}

Naive_NAMESPACE_END(geometry);
