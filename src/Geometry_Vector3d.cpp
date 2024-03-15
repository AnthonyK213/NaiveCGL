#include <naivecgl/Geometry/Vector3d.h>
#include <naivecgl/Math/Constants.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Vector3d::Vector3d()
    : myXYZ(math::UnsetValue, math::UnsetValue, math::UnsetValue) {}

Vector3d::Vector3d(const Naive_Real theX, const Naive_Real theY,
                   const Naive_Real theZ)
    : myXYZ(theX, theY, theZ) {}

Vector3d::Vector3d(const Naive_XYZ &theXYZ) : myXYZ(theXYZ) {}

Vector3d::Vector3d(const Naive_Vector3d_T &theVec)
    : myXYZ(theVec.x, theVec.y, theVec.z) {}

const Vector3d &Vector3d::Unset() {
  static Vector3d aPoint{};
  return aPoint;
}

Naive_Bool Vector3d::IsValid() const {
  return math::IsValidDouble(myXYZ.x()) && math::IsValidDouble(myXYZ.y()) &&
         math::IsValidDouble(myXYZ.z());
}

Naive_Bool Vector3d::Normalize() {
  if (IsValid() && !IsZero()) {
    myXYZ.normalize();
    return true;
  }

  return false;
}

Naive_NAMESPACE_END(geometry);
