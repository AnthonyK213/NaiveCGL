#include <naivecgl/Geometry/Plane.h>

Naive_NAMESPACE_BEGIN(geometry);

Plane::Plane(const Naive_Point3d &thePoint, const Naive_Vector3d &theXAxis,
             const Naive_Vector3d &theYAxis)
    : myLocation(thePoint), myXAxis(theXAxis) {
  myXAxis.normalize();
  myZAxis = theXAxis.cross(theYAxis);
  myZAxis.normalize();
  myYAxis = myZAxis.cross(myXAxis);
  myYAxis.normalize();
}

Naive_EXPORT Naive_Bool Plane::IsValid() const {
  if (myXAxis.isZero())
    return false;

  if (myYAxis.isZero())
    return false;

  if (myZAxis.isZero())
    return false;

  return true;
}

Naive_Real Plane::Distance(const Naive_Point3d &thePoint) const {
  Naive_Real aDist = (myZAxis.x() * (thePoint.x() - myLocation.x()) +
                      myZAxis.y() * (thePoint.y() - myLocation.y()) +
                      myZAxis.z() * (thePoint.z() - myLocation.z()));

  if (aDist < 0)
    aDist = -aDist;

  return aDist;
}

Naive_NAMESPACE_END(geometry);
