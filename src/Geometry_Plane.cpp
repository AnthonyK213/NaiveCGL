#include <naivecgl/Geometry/Plane.h>

Naive_NAMESPACE_BEGIN(geometry);

Plane::Plane() {}

Plane::Plane(const Naive_Pln &thePln) { myPos = thePln.Ax2(); }

Naive_Bool Plane::IsValid() const { return myPos.IsValid(); }

Handle_Naive_Geometry Plane::Clone() const { return new Plane(myPos); }

Naive_Pnt3d Plane::PointAt(const Naive_Real theU, const Naive_Real theV) const {
  if (!IsValid())
    return Naive_Pnt3d::Unset();
  return myPos.Location() + theU * myPos.XDirection() +
         theV * myPos.YDirection();
}

Naive_Code Plane::Evaluate(const Naive_Real theU, const Naive_Real theV,
                           const Naive_Integer theN,
                           Naive_Vec3dList1 &theD) const {
  Naive_TODO;
}

Naive_Real Plane::Distance(const Naive_Pnt3d &theP) const {
  Naive_Pln aPln{myPos};
  return aPln.Distance(theP);
}

Naive_NAMESPACE_END(geometry);
