#include <naivecgl/Geometry/Plane.h>

Naive_NAMESPACE_BEGIN(geometry);

Plane::Plane()
    : myLocation(0, 0, 0), myXAxis(1, 0, 0), myYAxis(0, 1, 0),
      myZAxis(0, 0, 1) {}

Plane::Plane(const Naive_Plane_T &thePlane) : myLocation(thePlane.origin) {
  myXAxis = thePlane.xAxis;
  myYAxis = thePlane.yAxis;
  if (myXAxis.IsZero())
    return;
  myXAxis.Normalize();
  myZAxis = myXAxis.Crossed(myYAxis);
  if (myZAxis.IsZero())
    return;
  myZAxis.Normalize();
  myYAxis = myZAxis.Crossed(myXAxis);
  if (myYAxis.IsZero())
    return;
  myYAxis.Normalize();
}

Plane::Plane(const Naive_Point3d &thePoint, const Naive_Vector3d &theXAxis,
             const Naive_Vector3d &theYAxis)
    : myLocation(thePoint), myXAxis(theXAxis) {
  if (myXAxis.IsZero())
    return;
  myXAxis.Normalize();
  myZAxis = theXAxis.Crossed(theYAxis);
  if (myZAxis.IsZero())
    return;
  myZAxis.Normalize();
  myYAxis = myZAxis.Crossed(myXAxis);
  if (myYAxis.IsZero())
    return;
  myYAxis.Normalize();
}

Naive_Bool Plane::IsValid() const {
  return myXAxis.IsValid() && myYAxis.IsValid() && myZAxis.IsValid();
}

Naive_Real Plane::Distance(const Naive_Point3d &thePoint) const {
  Naive_Real aDist = (myZAxis.X() * (thePoint.X() - myLocation.X()) +
                      myZAxis.Y() * (thePoint.Y() - myLocation.Y()) +
                      myZAxis.Z() * (thePoint.Z() - myLocation.Z()));

  if (aDist < 0)
    aDist = -aDist;

  return aDist;
}

Naive_NAMESPACE_END(geometry);
