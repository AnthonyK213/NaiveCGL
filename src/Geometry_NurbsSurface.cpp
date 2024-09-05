#include <naivecgl/Geometry/NurbsSurface.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Polynomial.h>
#include <naivecgl/Math/Trsf3d.h>

Naive_NAMESPACE_BEGIN(geometry);

Naive_IMPLEMENT_RTTI(NurbsSurface);

NurbsSurface::NurbsSurface() noexcept
    : myUDegree(0), myVDegree(0), myURational(Naive_False),
      myVRational(Naive_False), myUPeriodic(Naive_False),
      myVPeriodic(Naive_False) {}

NurbsSurface::NurbsSurface(
    const Naive_Pnt3dList2 &thePoles, const Naive_RealList2 &theWeights,
    const Naive_RealList1 &theUKnots, const Naive_RealList1 &theVKnots,
    const Naive_IntegerList1 &theUMults, const Naive_IntegerList1 &theVMults,
    const Naive_Integer theUDegree, const Naive_Integer theVDegree,
    const Naive_Bool theUPeriodic, const Naive_Bool theVPeriodic) noexcept
    : myUDegree(0), myVDegree(0), myURational(Naive_False),
      myVRational(Naive_False), myUPeriodic(Naive_False),
      myVPeriodic(Naive_False) {
  Init(thePoles, theWeights, theUKnots, theVKnots, theUMults, theVMults,
       theUDegree, theVDegree, theUPeriodic, theVPeriodic);
}

Naive_Code NurbsSurface::Init(
    const Naive_Pnt3dList2 &thePoles, const Naive_RealList2 &theWeights,
    const Naive_RealList1 &theUKnots, const Naive_RealList1 &theVKnots,
    const Naive_IntegerList1 &theUMults, const Naive_IntegerList1 &theVMults,
    const Naive_Integer theUDegree, const Naive_Integer theVDegree,
    const Naive_Bool theUPeriodic, const Naive_Bool theVPeriodic) noexcept {
  Naive_Integer aPU, aPV, aWU, aWV;
  if (math::Util::List2CheckBound(thePoles, aPU, aPV) ||
      math::Util::List2CheckBound(theWeights, aWU, aWV))
    return Naive_Code_invalid_value;

  if (aPU < 2 || aPV < 2)
    return Naive_Code_value_out_of_range;

  if (aPU != aWU || aPV != aWV)
    return Naive_Code_poles_weights_not_match;

  Naive_XYZWList2 aCPs(aPU, Naive_XYZWList1(aPV));

  for (Naive_Integer u = 0; u < aPU; ++u) {
    for (Naive_Integer v = 0; v < aPV; ++v) {
      aCPs[u][v] = thePoles[u][v].HomoCoord() * theWeights[u][v];
    }
  }

  return update(::std::move(aCPs), theUKnots, theVKnots, theUMults, theVMults,
                theUDegree, theVDegree, theUPeriodic, theVPeriodic);
}

Naive_Bool NurbsSurface::IsValid() const {
  return myUDegree > 0 && myVDegree > 0;
}

Handle_Naive_Geometry NurbsSurface::Clone() const {
  return new NurbsSurface(*this);
}

Naive_Bool NurbsSurface::Bounds(Naive_Real &theU0, Naive_Real &theU1,
                                Naive_Real &theV0, Naive_Real &theV1) const {
  if (!IsValid())
    return Naive_False;

  theU0 = myUKnots[0];
  theU1 = myUKnots[myUKnots.size() - 1];
  theV0 = myVKnots[0];
  theV1 = myVKnots[myVKnots.size() - 1];

  return Naive_True;
}

Naive_Code NurbsSurface::Evaluate(const Naive_Real theU, const Naive_Real theV,
                                  const Naive_Integer theN,
                                  Naive_Vec3dList1 &theD) const {
  if (!IsValid())
    return Naive_Code_invalid_object;

  return math::Nurbs::SurfaceEvaluate(
      myCPs, myUFlatKnots, myVFlatKnots, myUKnots, myVKnots, myUMults, myVMults,
      myUDegree, myVDegree, theU, theV, theN, theD);
}

Naive_Bool NurbsSurface::IsUClosed() const { return Naive_False; }

Naive_Bool NurbsSurface::IsVClosed() const { return Naive_False; }

Naive_Bool NurbsSurface::IsUPeriodic() const { return myUPeriodic; }

Naive_Bool NurbsSurface::IsVPeriodic() const { return myVPeriodic; }

Naive_Real NurbsSurface::UPeriod() const { return math::Constant::UnsetReal(); }

Naive_Real NurbsSurface::VPeriod() const { return math::Constant::UnsetReal(); }

Naive_Code NurbsSurface::transform(const Naive_Trsf3d &theTrsf) {
  return Naive_Code_not_implemented;
}

Naive_NAMESPACE_END(geometry);
