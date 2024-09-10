#include <naivecgl/BRep/CurveOnSurface.h>
#include <naivecgl/Geometry/Surface.h>
#include <naivecgl/Geometry2d/Curve.h>
#include <naivecgl/Math/Constant.h>

Naive_NAMESPACE_BEGIN(brep);

Naive_IMPLEMENT_RTTI(CurveOnSurface);

CurveOnSurface::CurveOnSurface(const Handle_Naive_Surface &theSrf,
                               const Handle_Naive_Curve2d &thePCrv)
    : mySrf(theSrf), myPCrv(thePCrv) {}

Naive_Bool CurveOnSurface::IsValid() const {
  return mySrf && myPCrv && mySrf->IsValid() && myPCrv->IsValid();
}

Handle_Naive_Geometry CurveOnSurface::Clone() const {
  if (!IsValid())
    return nullptr;

  Handle_Naive_Surface srf = Handle_Naive_Surface::DownCast(mySrf->Clone());
  Handle_Naive_Curve2d crv = Handle_Naive_Curve2d::DownCast(myPCrv->Clone());
  return new CurveOnSurface(srf, crv);
}

Naive_Real CurveOnSurface::FirstParameter() const {
  return IsValid() ? myPCrv->FirstParameter() : math::Constant::UnsetReal();
}

Naive_Real CurveOnSurface::LastParameter() const {
  return IsValid() ? myPCrv->LastParameter() : math::Constant::UnsetReal();
}

Naive_Pnt3d CurveOnSurface::PointAt(const Naive_Real theT) const {
  if (IsValid()) {
    Naive_Pnt2d aUV = myPCrv->PointAt(theT);
    if (aUV.IsValid()) {
      return mySrf->PointAt(aUV.X(), aUV.Y());
    }
  }

  return Naive_Pnt3d::Unset();
}

Naive_Vec3d CurveOnSurface::TangentAt(const Naive_Real theT) const {
  return Naive_Vec3d::Unset();
}

Naive_Code CurveOnSurface::Evaluate(const Naive_Real theT,
                                    const Naive_Integer theN,
                                    Naive_Vec3dList1 &theD) const {
  return Naive_Code_not_implemented;
}

Naive_Code CurveOnSurface::CurvatureAt(const Naive_Real theT,
                                       Naive_Vec3d &theV) const {
  return Naive_Code_not_implemented;
}

Naive_Bool CurveOnSurface::IsClosed() const { return Naive_False; }

Naive_Bool CurveOnSurface::IsPeriodic() const { return Naive_False; }

Naive_Real CurveOnSurface::Period() const {
  return math::Constant::UnsetReal();
}

Naive_Code CurveOnSurface::transform(const math::Trsf3d &theTrsf) {
  if (!IsValid())
    return Naive_Code_invalid_object;

  return mySrf->Transform(theTrsf);
}

Handle_Naive_Curve CurveOnSurface::ComputeCurve3d() const {
  if (!IsValid())
    return nullptr;

  return nullptr;
}

Naive_NAMESPACE_END(brep);
