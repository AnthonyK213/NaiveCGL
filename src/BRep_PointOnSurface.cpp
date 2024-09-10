#include <naivecgl/BRep/PointOnSurface.h>
#include <naivecgl/Geometry/Surface.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(brep);

PointOnSurface::PointOnSurface(const Naive_Handle<geometry::Surface> &theSrf,
                               const Naive_Real theU, const Naive_Real theV)
    : mySrf(theSrf), myU(theU), myV(theV) {}

Naive_Pnt3d PointOnSurface::Pnt() const {
  return IsValid() ? mySrf->PointAt(myU, myV) : Naive_Pnt3d::Unset();
}

Naive_Real PointOnSurface::X() const { return Pnt().X(); }

Naive_Real PointOnSurface::Y() const { return Pnt().Y(); }

Naive_Real PointOnSurface::Z() const { return Pnt().Z(); }

Naive_Bool PointOnSurface::IsValid() const {
  return mySrf && mySrf->IsValid() && math::Util::IsValidReal(myU);
}

Handle_Naive_Geometry PointOnSurface::Clone() const {
  if (!IsValid())
    return nullptr;

  Handle_Naive_Surface srf = Handle_Naive_Surface::DownCast(mySrf->Clone());
  return new PointOnSurface(srf, myU, myV);
}

Naive_Code PointOnSurface::transform(const Naive_Trsf3d &theTrsf) {
  if (!IsValid())
    return Naive_Code_invalid_object;

  return mySrf->Transform(theTrsf);
}

Naive_NAMESPACE_END(brep);
