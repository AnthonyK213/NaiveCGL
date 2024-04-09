#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Geometry/Transform3d.h>
#include <naivecgl/Geometry/Vector3d.h>
#include <naivecgl/Math/Constants.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Point3d::Point3d()
    : myXYZ(math::UnsetValue, math::UnsetValue, math::UnsetValue) {}

Point3d::Point3d(const Naive_Real theX, const Naive_Real theY,
                 const Naive_Real theZ)
    : myXYZ(theX, theY, theZ) {}

Point3d::Point3d(const Naive_XYZ &theXYZ) : myXYZ(theXYZ) {}

Point3d::Point3d(const Naive_Point3d_T &thePnt)
    : myXYZ(thePnt.x, thePnt.y, thePnt.z) {}

const Point3d &Point3d::Origin() {
  static Point3d aPoint{0., 0., 0.};
  return aPoint;
}

const Point3d &Point3d::Unset() {
  static Point3d aPoint{};
  return aPoint;
}

Naive_Bool Point3d::IsValid() const {
  return math::Util::IsValidDouble(myXYZ.x()) &&
         math::Util::IsValidDouble(myXYZ.y()) &&
         math::Util::IsValidDouble(myXYZ.z());
}

Naive_Real Point3d::DistanceTo(const Point3d &thePoint) const {
  if (!IsValid() || !thePoint.IsValid())
    return math::UnsetValue;
  return (myXYZ - thePoint.myXYZ).norm();
}

Naive_Real Point3d::DistanceToSquared(const Point3d &thePoint) const {
  if (!IsValid() || !thePoint.IsValid())
    return math::UnsetValue;
  return (myXYZ - thePoint.myXYZ).squaredNorm();
}

Vector3d Point3d::Subtracted(const Point3d &thePoint) const {
  if (!IsValid() || !thePoint.IsValid())
    return Vector3d::Unset();
  return {myXYZ - thePoint.myXYZ};
}

Naive_Bool Point3d::Transform(const Transform3d &theTrsf) {
  if (!IsValid() || !theTrsf.IsValid())
    return false;
  myXYZ = theTrsf.Trsf() * myXYZ;
  return true;
}

Point3d Point3d::Transformed(const Transform3d &theTrsf) const {
  Point3d aPnt(*this);
  if (aPnt.Transform(theTrsf))
    return aPnt;
  return Point3d::Unset();
}

Naive_Bool Point3d::Dump(Naive_Point3d_T &theP) const {
  if (!IsValid())
    return false;
  theP.x = X();
  theP.y = Y();
  theP.z = Z();
  return true;
}

const Vector3d Point3d::operator-(const Point3d &thePoint) const {
  return Subtracted(thePoint);
}

Naive_NAMESPACE_END(geometry);
