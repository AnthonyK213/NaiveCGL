#include <naivecgl/Geometry/Point3d.h>
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
  return math::IsValidDouble(myXYZ.x()) && math::IsValidDouble(myXYZ.y()) &&
         math::IsValidDouble(myXYZ.z());
}

Naive_Real Point3d::DistanceTo(const Point3d &thePoint) const {
  return (myXYZ - thePoint.myXYZ).norm();
}

Naive_Real Point3d::DistanceToSquared(const Point3d &thePoint) const {
  return (myXYZ - thePoint.myXYZ).squaredNorm();
}

Vector3d Point3d::Subtracted(const Point3d &thePoint) const {
  return myXYZ - thePoint.myXYZ;
}

void Point3d::Dump(Naive_Point3d_T &theP) const {
  theP.x = X();
  theP.y = Y();
  theP.z = Z();
}

const Vector3d Point3d::operator-(const Point3d &thePoint) const {
  return Subtracted(thePoint);
}

Naive_NAMESPACE_END(geometry);
