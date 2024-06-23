#include <naivecgl/Geometry/Plane.h>

Naive_NAMESPACE_BEGIN(geometry);

Plane::Plane() : myPln() {}

Plane::Plane(const Naive_Pln &thePln) : myPln(thePln) {}

Naive_Bool Plane::IsValid() const { return myPln.IsValid(); }

Handle_Naive_Geometry Plane::Clone() const { return new Plane(myPln); }

Naive_Pnt3d Plane::PointAt(const Naive_Real theU, const Naive_Real theV) const {
  Naive_TODO;
}

Naive_Code Plane::Evaluate(const Naive_Real theU, const Naive_Real theV,
                           const Naive_Integer theN,
                           Naive_Vec3dList1 &theD) const {
  Naive_TODO;
}

Naive_Real Plane::Distance(const Naive_Pnt3d &theP) const {
  return myPln.Distance(theP);
}

Naive_NAMESPACE_END(geometry);
