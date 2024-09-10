#include <naivecgl/BRep/PointOnCurve.h>
#include <naivecgl/Geometry/Curve.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(brep);

PointOnCurve::PointOnCurve(const Handle_Naive_Curve &theCrv,
                           const Naive_Real theT)
    : myCrv(theCrv), myT(theT) {}

Naive_Pnt3d PointOnCurve::Pnt() const {
  return IsValid() ? myCrv->PointAt(myT) : Naive_Pnt3d::Unset();
}

Naive_Real PointOnCurve::X() const { return Pnt().X(); }

Naive_Real PointOnCurve::Y() const { return Pnt().Y(); }

Naive_Real PointOnCurve::Z() const { return Pnt().Z(); }

Naive_Bool PointOnCurve::IsValid() const {
  return myCrv && myCrv->IsValid() && math::Util::IsValidReal(myT);
}

Handle_Naive_Geometry PointOnCurve::Clone() const {
  if (!IsValid())
    return nullptr;

  Handle_Naive_Curve crv = Handle_Naive_Curve::DownCast(myCrv->Clone());
  return new PointOnCurve(crv, myT);
}

Naive_Code PointOnCurve::transform(const Naive_Trsf3d &theTrsf) {
  if (!IsValid())
    return Naive_Code_invalid_object;

  return myCrv->Transform(theTrsf);
}

Naive_NAMESPACE_END(brep);
