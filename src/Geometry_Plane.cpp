#include <naivecgl/Geometry/Plane.h>

Naive_NAMESPACE_BEGIN(geometry);

Plane::Plane() {}

Plane::Plane(const Naive_Plane_T &thePlane)
    : myLocation(thePlane.origin), myXAxis(thePlane.xAxis),
      myYAxis(thePlane.yAxis) {
  initByXY();
}

Plane::Plane(const Naive_Point3d &thePoint, const Naive_Vector3d &theXAxis,
             const Naive_Vector3d &theYAxis)
    : myLocation(thePoint), myXAxis(theXAxis), myYAxis(theYAxis) {
  initByXY();
}

Plane::Plane(const Naive_Point3d &thePoint, const Naive_Vector3d &theNormal)
    : myZAxis(theNormal) {
  if (!myZAxis.Normalize())
    return;

  myXAxis = Vector3d::YAxis().Crossed(myZAxis);
  if (!myXAxis.Normalize()) {
    myXAxis = Vector3d::XAxis().Crossed(myZAxis);
  }

  myYAxis = myZAxis.Crossed(myXAxis);
  myYAxis.Normalize();
}

Naive_Bool Plane::IsValid() const {
  return myLocation.IsValid() && myXAxis.IsValid() && !myXAxis.IsZero() &&
         myYAxis.IsValid() && !myYAxis.IsZero() && myZAxis.IsValid() &&
         !myZAxis.IsZero();
}

Naive_Real Plane::Distance(const Naive_Point3d &thePoint) const {
  Naive_Real aDist = (myZAxis.X() * (thePoint.X() - myLocation.X()) +
                      myZAxis.Y() * (thePoint.Y() - myLocation.Y()) +
                      myZAxis.Z() * (thePoint.Z() - myLocation.Z()));

  if (aDist < 0)
    aDist = -aDist;

  return aDist;
}

const Plane &Plane::Unset() {
  static Plane aPlane{};
  return aPlane;
}

const Plane &Plane::WorldXY() {
  static Plane aPln{Point3d::Origin(), Vector3d::XAxis(), Vector3d::YAxis()};
  return aPln;
}

const Plane &Plane::WorldYZ() {
  static Plane aPln{Point3d::Origin(), Vector3d::YAxis(), Vector3d::ZAxis()};
  return aPln;
}

const Plane &Plane::WorldZX() {
  static Plane aPln{Point3d::Origin(), Vector3d::ZAxis(), Vector3d::XAxis()};
  return aPln;
}

Naive_Bool Plane::Transform(const Transform3d &theTrsf) {
  if (!myLocation.Transform(theTrsf) || !myXAxis.Transform(theTrsf) ||
      !myYAxis.Transform(theTrsf))
    return false;

  initByXY();
  return true;
}

Plane Plane::Transformed(const Transform3d &theTrsf) const {
  Plane aPlane(*this);
  if (aPlane.Transform(theTrsf))
    return aPlane;
  return Unset();
}

Naive_Bool Plane::Orient(const Plane &thePln, Transform3d &theTrsf) const {
  if (!IsValid() || !thePln.IsValid())
    return false;

  Naive_Trsf aT1{};
  aT1.setIdentity();
  Naive_Matrix3d aR1{};
  aR1.col(0) = myXAxis.XYZ();
  aR1.col(1) = myYAxis.XYZ();
  aR1.col(2) = myZAxis.XYZ();
  aT1.rotate(aR1);
  aT1.translation() = myLocation.XYZ();

  Naive_Trsf aT2{};
  aT2.setIdentity();
  Naive_Matrix3d aR2{};
  aR2.col(0) = thePln.myXAxis.XYZ();
  aR2.col(1) = thePln.myYAxis.XYZ();
  aR2.col(2) = thePln.myZAxis.XYZ();
  aT2.rotate(aR2);
  aT2.translation() = thePln.myLocation.XYZ();

  theTrsf = {aT2 * aT1.inverse()};
  return true;
}

void Plane::initByXY() {
  if (!myXAxis.Normalize())
    return;

  myZAxis = myXAxis.Crossed(myYAxis);
  if (!myZAxis.Normalize())
    return;

  myYAxis = myZAxis.Crossed(myXAxis);
  if (!myYAxis.Normalize())
    return;
}

Naive_NAMESPACE_END(geometry);
