#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Geometry/Transform3d.h>
#include <naivecgl/Geometry/Vector3d.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Vector3d::Vector3d()
    : myXYZ(math::UnsetValue, math::UnsetValue, math::UnsetValue) {}

Vector3d::Vector3d(const Naive_Point3d &thePoint) : myXYZ(thePoint.XYZ()) {}

Vector3d::Vector3d(const Naive_Real theX, const Naive_Real theY,
                   const Naive_Real theZ)
    : myXYZ(theX, theY, theZ) {}

Vector3d::Vector3d(const Naive_XYZ &theXYZ) : myXYZ(theXYZ) {}

Vector3d::Vector3d(const Naive_Vector3d_T &theVec)
    : myXYZ(theVec.x, theVec.y, theVec.z) {}

Naive_Bool Vector3d::IsValid() const {
  return math::IsValidDouble(X()) && math::IsValidDouble(Y()) &&
         math::IsValidDouble(Z());
}

Naive_Bool Vector3d::IsUnitVector() const {
  return std::abs(Length() - 1.) <= math::Epsilon;
}

Naive_Bool Vector3d::IsZero() const {
  return myXYZ.isZero(math::ZeroTolerance);
}

Naive_Real Vector3d::Length() const {
  if (!IsValid())
    return math::UnsetValue;
  return myXYZ.norm();
}

Naive_Real Vector3d::SquareLength() const {
  if (!IsValid())
    return math::UnsetValue;
  return myXYZ.squaredNorm();
}

Naive_Bool Vector3d::Normalize() {
  if (IsValid() && !IsZero()) {
    myXYZ.normalize();
    return true;
  }

  return false;
}

const Vector3d &Vector3d::XAxis() {
  static Vector3d aVector{Naive_XYZ::UnitX()};
  return aVector;
}

const Vector3d &Vector3d::YAxis() {
  static Vector3d aVector{Naive_XYZ::UnitY()};
  return aVector;
}

const Vector3d &Vector3d::ZAxis() {
  static Vector3d aVector{Naive_XYZ::UnitZ()};
  return aVector;
}

const Vector3d &Vector3d::Zero() {
  static Vector3d aVector{Naive_XYZ::Zero()};
  return aVector;
}

const Vector3d &Vector3d::Unset() {
  static Vector3d aVector{};
  return aVector;
}

void Vector3d::Add(const Vector3d &theVec) {
  if (!IsValid() || !theVec.IsValid())
    return;
  myXYZ += theVec.myXYZ;
}

Vector3d Vector3d::Added(const Vector3d &theVec) const {
  if (!IsValid() || !theVec.IsValid())
    return Unset();
  return {myXYZ + theVec.myXYZ};
}

void Vector3d::Subtract(const Vector3d &theVec) {
  if (!IsValid() || !theVec.IsValid())
    return;
  myXYZ -= theVec.myXYZ;
}

Vector3d Vector3d::Subtracted(const Vector3d &theVec) const {
  if (!IsValid() || !theVec.IsValid())
    return Unset();
  return {myXYZ - theVec.myXYZ};
}

void Vector3d::Multiply(const Naive_Real theT) {
  if (IsValid())
    myXYZ *= theT;
}

Vector3d Vector3d::Multiplied(const Naive_Real theT) const {
  if (!IsValid())
    return Unset();
  return {myXYZ * theT};
}

void Vector3d::Divide(const Naive_Real theT) {
  if (!IsValid() || std::abs(theT) < math::ZeroTolerance)
    return;
  myXYZ /= theT;
}

Vector3d Vector3d::Divided(const Naive_Real theT) const {
  if (!IsValid() || std::abs(theT) < math::ZeroTolerance)
    return Unset();
  return {myXYZ / theT};
}

void Vector3d::Negate() {
  if (IsValid())
    myXYZ = -myXYZ;
}

Vector3d Vector3d::Negated() const {
  if (!IsValid())
    return Unset();
  return {-myXYZ};
}

Naive_Real Vector3d::Dot(const Vector3d &theVec) const {
  if (!IsValid() || theVec.IsValid())
    return math::UnsetValue;
  return myXYZ.dot(theVec.myXYZ);
}

void Vector3d::Cross(const Vector3d &theVec) {
  if (!IsValid() || theVec.IsValid())
    return;
  myXYZ = myXYZ.cross(theVec.myXYZ);
}

Vector3d Vector3d::Crossed(const Vector3d &theVec) const {
  if (!IsValid() || theVec.IsValid())
    return Unset();
  return myXYZ.cross(theVec.myXYZ);
}

Naive_Bool Vector3d::EpsilonEquals(const Vector3d &theVec,
                                   const Naive_Real theE) {
  return math::EpsilonEquals(X(), theVec.X(), theE) &&
         math::EpsilonEquals(Y(), theVec.Y(), theE) &&
         math::EpsilonEquals(Z(), theVec.Z(), theE);
}

Naive_Bool Vector3d::Reverse() {
  if (!IsValid())
    return false;
  Negate();
  return true;
}

Naive_Bool Vector3d::Equals(const Vector3d &theVec) {
  return myXYZ == theVec.myXYZ;
}

Naive_Bool Vector3d::Transform(const Transform3d &theTrsf) {
  if (!IsValid() || !theTrsf.IsValid())
    return false;
  myXYZ = theTrsf.Trsf() * myXYZ;
  return true;
}

Vector3d Vector3d::Transformed(const Transform3d &theTrsf) const {
  Vector3d aVec(myXYZ);
  if (aVec.Transform(theTrsf))
    return aVec;
  return Unset();
}

Naive_NAMESPACE_END(geometry);
