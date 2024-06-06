#include <naivecgl/Geometry/Point3d.h>
#include <naivecgl/Geometry/Transform3d.h>
#include <naivecgl/Geometry/Vector3d.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Vector3d::Vector3d()
    : myXYZ(math::Constant::UnsetReal(), math::Constant::UnsetReal(),
            math::Constant::UnsetReal()) {}

Vector3d::Vector3d(const Naive_Point3d &thePoint) : myXYZ(thePoint.XYZ()) {}

Vector3d::Vector3d(const Naive_Real theX, const Naive_Real theY,
                   const Naive_Real theZ)
    : myXYZ(theX, theY, theZ) {}

Vector3d::Vector3d(const Naive_XYZ &theXYZ) : myXYZ(theXYZ) {}

Vector3d::Vector3d(const Naive_Vector3d_t &theVec)
    : myXYZ(theVec.x, theVec.y, theVec.z) {}

Naive_Bool Vector3d::IsValid() const {
  return math::Util::IsValidReal(X()) && math::Util::IsValidReal(Y()) &&
         math::Util::IsValidReal(Z());
}

Naive_Bool Vector3d::IsUnitVector() const {
  return ::std::abs(Length() - 1.) <= math::Constant::Epsilon();
}

Naive_Bool Vector3d::IsZero() const {
  return myXYZ.isZero(math::Constant::ZeroTolerance());
}

Naive_Real Vector3d::Length() const {
  if (!IsValid())
    return math::Constant::UnsetReal();
  return myXYZ.norm();
}

Naive_Real Vector3d::SquareLength() const {
  if (!IsValid())
    return math::Constant::UnsetReal();
  return myXYZ.squaredNorm();
}

Naive_Bool Vector3d::Normalize() {
  if (IsValid() && !IsZero()) {
    myXYZ.normalize();
    return true;
  }

  return false;
}

Naive_EXPORT Vector3d Vector3d::Normalized() const {
  Vector3d aV(*this);
  if (aV.Normalize())
    return aV;
  return Unset();
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

Naive_Bool Vector3d::Add(const Vector3d &theVec) {
  if (IsValid() && theVec.IsValid()) {
    myXYZ += theVec.myXYZ;
    return true;
  }
  return false;
}

Vector3d Vector3d::Added(const Vector3d &theVec) const {
  Vector3d aVec(*this);
  return aVec.Add(theVec) ? aVec : Unset();
}

Naive_Bool Vector3d::Subtract(const Vector3d &theVec) {
  if (IsValid() && theVec.IsValid()) {
    myXYZ -= theVec.myXYZ;
    return true;
  }
  return false;
}

Vector3d Vector3d::Subtracted(const Vector3d &theVec) const {
  Vector3d aVec(*this);
  return aVec.Subtract(theVec) ? aVec : Unset();
}

Naive_Bool Vector3d::Multiply(const Naive_Real theT) {
  if (IsValid() && math::Util::IsValidReal(theT)) {
    myXYZ *= theT;
    return true;
  }
  return false;
}

Vector3d Vector3d::Multiplied(const Naive_Real theT) const {
  Vector3d aVec(*this);
  return aVec.Multiply(theT) ? aVec : Unset();
}

Naive_Bool Vector3d::Divide(const Naive_Real theT) {
  if (IsValid() && !math::Util::EpsilonEquals(theT, 0.0)) {
    myXYZ /= theT;
    return true;
  }
  return false;
}

Vector3d Vector3d::Divided(const Naive_Real theT) const {
  Vector3d aVec(*this);
  return aVec.Divide(theT) ? aVec : Unset();
}

void Vector3d::Negate() { myXYZ = -myXYZ; }

Vector3d Vector3d::Negated() const { return {-myXYZ}; }

Naive_Real Vector3d::Dot(const Vector3d &theVec) const {
  return (IsValid() && theVec.IsValid()) ? myXYZ.dot(theVec.myXYZ)
                                         : math::Constant::UnsetReal();
}

void Vector3d::Cross(const Vector3d &theVec) {
  if (IsValid() && theVec.IsValid())
    myXYZ = myXYZ.cross(theVec.myXYZ);
}

Vector3d Vector3d::Crossed(const Vector3d &theVec) const {
  return (IsValid() && theVec.IsValid()) ? myXYZ.cross(theVec.myXYZ) : Unset();
}

Naive_Bool Vector3d::EpsilonEquals(const Vector3d &theVec,
                                   const Naive_Real theE) {
  return math::Util::EpsilonEquals(X(), theVec.X(), theE) &&
         math::Util::EpsilonEquals(Y(), theVec.Y(), theE) &&
         math::Util::EpsilonEquals(Z(), theVec.Z(), theE);
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
  if (IsValid() && theTrsf.IsValid()) {
    myXYZ = theTrsf.Trsf().rotation() * myXYZ;
    return true;
  }
  return false;
}

Vector3d Vector3d::Transformed(const Transform3d &theTrsf) const {
  Vector3d aVec(myXYZ);
  return aVec.Transform(theTrsf) ? aVec : Unset();
}

Naive_Bool Vector3d::Dump(Naive_Vector3d_t &theVec) const {
  if (!IsValid())
    return false;
  theVec.x = X();
  theVec.y = Y();
  theVec.z = Z();
  return true;
}

const Vector3d operator+(const Vector3d &theVec1, const Vector3d &theVec2) {
  return theVec1.Added(theVec2);
}

const Vector3d operator-(const Vector3d &theVec1, const Vector3d &theVec2) {
  return theVec1.Subtracted(theVec2);
}

const Vector3d operator-(const Vector3d &theVec) { return theVec.Negated(); }

const Vector3d operator*(const Vector3d &theVec, const Naive_Real theT) {
  return theVec.Multiplied(theT);
}

const Vector3d operator*(const Naive_Real theT, const Vector3d &theVec) {
  return theVec.Multiplied(theT);
}

const Naive_Real operator*(const Vector3d theVec1, const Vector3d &theVec2) {
  return theVec1.Dot(theVec2);
}

const Vector3d operator/(const Vector3d &theVec, const Naive_Real theT) {
  return theVec.Divided(theT);
}

Naive_NAMESPACE_END(geometry);
