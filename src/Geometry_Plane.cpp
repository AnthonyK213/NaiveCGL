#include <naivecgl/Geometry/Plane.h>

Naive_NAMESPACE_BEGIN(geometry);

Plane::Plane()
    : myLocation(0, 0, 0), myXAxis(1, 0, 0), myYAxis(0, 1, 0),
      myZAxis(0, 0, 1) {}

Plane::Plane(const Naive_Plane_T &thePlane) {
  myLocation = Naive_POINT3D(thePlane.origin);
  myXAxis = Naive_VECTOR3D(thePlane.xAxis);
  myYAxis = Naive_VECTOR3D(thePlane.yAxis);
  if (myXAxis.isZero())
    return;
  myXAxis.normalize();
  myZAxis = myXAxis.cross(myYAxis);
  if (myZAxis.isZero())
    return;
  myZAxis.normalize();
  myYAxis = myZAxis.cross(myXAxis);
  if (myYAxis.isZero())
    return;
  myYAxis.normalize();
}

Plane::Plane(const Naive_Point3d &thePoint, const Naive_Vector3d &theXAxis,
             const Naive_Vector3d &theYAxis)
    : myLocation(thePoint), myXAxis(theXAxis) {
  if (myXAxis.isZero())
    return;
  myXAxis.normalize();
  myZAxis = theXAxis.cross(theYAxis);
  if (myZAxis.isZero())
    return;
  myZAxis.normalize();
  myYAxis = myZAxis.cross(myXAxis);
  if (myYAxis.isZero())
    return;
  myYAxis.normalize();
}

Naive_Bool Plane::IsValid() const {
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
