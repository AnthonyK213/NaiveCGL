#include <naivecgl/Math/Pnt3d.h>
#include <naivecgl/Math/Trsf3d.h>
#include <naivecgl/Math/Util.h>
#include <naivecgl/Math/Vec3d.h>

Naive_NAMESPACE_BEGIN(math);

Vec3d::Vec3d()
    : myXYZ(Constant::UnsetReal(), Constant::UnsetReal(),
            Constant::UnsetReal()) {}

Vec3d::Vec3d(const Naive_Pnt3d &thePoint) : myXYZ(thePoint.XYZ()) {}

Vec3d::Vec3d(const Naive_Real theX, const Naive_Real theY,
             const Naive_Real theZ)
    : myXYZ(theX, theY, theZ) {}

Vec3d::Vec3d(const Naive_XYZ &theXYZ) : myXYZ(theXYZ) {}

Vec3d::Vec3d(const Naive_Vector3d_t &theVec)
    : myXYZ(theVec.x, theVec.y, theVec.z) {}

Naive_Bool Vec3d::IsValid() const {
  return Util::IsValidReal(X()) && Util::IsValidReal(Y()) &&
         Util::IsValidReal(Z());
}

Naive_Bool Vec3d::IsUnitVector() const {
  return ::std::abs(Length() - 1.) <= Constant::Epsilon();
}

Naive_Bool Vec3d::IsZero() const {
  return myXYZ.isZero(Constant::ZeroTolerance());
}

Naive_Real Vec3d::Length() const {
  if (!IsValid())
    return Constant::UnsetReal();
  return myXYZ.norm();
}

Naive_Real Vec3d::SquareLength() const {
  if (!IsValid())
    return Constant::UnsetReal();
  return myXYZ.squaredNorm();
}

Naive_Bool Vec3d::Normalize() {
  if (IsValid() && !IsZero()) {
    myXYZ.normalize();
    return Naive_True;
  }

  return Naive_False;
}

Naive_EXPORT Vec3d Vec3d::Normalized() const {
  Vec3d aV(*this);
  if (aV.Normalize())
    return aV;
  return Unset();
}

const Vec3d &Vec3d::XAxis() {
  static Vec3d aVector{Naive_XYZ::UnitX()};
  return aVector;
}

const Vec3d &Vec3d::YAxis() {
  static Vec3d aVector{Naive_XYZ::UnitY()};
  return aVector;
}

const Vec3d &Vec3d::ZAxis() {
  static Vec3d aVector{Naive_XYZ::UnitZ()};
  return aVector;
}

const Vec3d &Vec3d::Zero() {
  static Vec3d aVector{Naive_XYZ::Zero()};
  return aVector;
}

const Vec3d &Vec3d::Unset() {
  static Vec3d aVector{};
  return aVector;
}

Naive_Bool Vec3d::Add(const Vec3d &theVec) {
  if (IsValid() && theVec.IsValid()) {
    myXYZ += theVec.myXYZ;
    return Naive_True;
  }
  return Naive_False;
}

Vec3d Vec3d::Added(const Vec3d &theVec) const {
  Vec3d aVec(*this);
  return aVec.Add(theVec) ? aVec : Unset();
}

Naive_Bool Vec3d::Subtract(const Vec3d &theVec) {
  if (IsValid() && theVec.IsValid()) {
    myXYZ -= theVec.myXYZ;
    return Naive_True;
  }
  return Naive_False;
}

Vec3d Vec3d::Subtracted(const Vec3d &theVec) const {
  Vec3d aVec(*this);
  return aVec.Subtract(theVec) ? aVec : Unset();
}

Naive_Bool Vec3d::Multiply(const Naive_Real theT) {
  if (IsValid() && Util::IsValidReal(theT)) {
    myXYZ *= theT;
    return Naive_True;
  }
  return Naive_False;
}

Vec3d Vec3d::Multiplied(const Naive_Real theT) const {
  Vec3d aVec(*this);
  return aVec.Multiply(theT) ? aVec : Unset();
}

Naive_Bool Vec3d::Divide(const Naive_Real theT) {
  if (IsValid() && !Util::EpsilonEquals(theT, 0.0)) {
    myXYZ /= theT;
    return Naive_True;
  }
  return Naive_False;
}

Vec3d Vec3d::Divided(const Naive_Real theT) const {
  Vec3d aVec(*this);
  return aVec.Divide(theT) ? aVec : Unset();
}

void Vec3d::Negate() { myXYZ = -myXYZ; }

Vec3d Vec3d::Negated() const { return {-myXYZ}; }

Naive_Real Vec3d::Dot(const Vec3d &theVec) const {
  return (IsValid() && theVec.IsValid()) ? myXYZ.dot(theVec.myXYZ)
                                         : Constant::UnsetReal();
}

Naive_Bool Vec3d::Cross(const Vec3d &theVec) {
  if (IsValid() && theVec.IsValid()) {
    myXYZ = myXYZ.cross(theVec.myXYZ);
    return Naive_True;
  }
  return Naive_False;
}

Vec3d Vec3d::Crossed(const Vec3d &theVec) const {
  Vec3d aVec(*this);
  return aVec.Cross(theVec) ? aVec : Unset();
}

Naive_Bool Vec3d::EpsilonEquals(const Vec3d &theVec, const Naive_Real theE) {
  return Util::EpsilonEquals(X(), theVec.X(), theE) &&
         Util::EpsilonEquals(Y(), theVec.Y(), theE) &&
         Util::EpsilonEquals(Z(), theVec.Z(), theE);
}

Naive_Bool Vec3d::Reverse() {
  if (!IsValid())
    return Naive_False;
  Negate();
  return Naive_True;
}

Naive_Bool Vec3d::Equals(const Vec3d &theVec) { return myXYZ == theVec.myXYZ; }

Naive_Bool Vec3d::Transform(const Trsf3d &theTrsf) {
  if (IsValid() && theTrsf.IsValid()) {
    myXYZ = theTrsf.Affine().rotation() * myXYZ;
    return Naive_True;
  }
  return Naive_False;
}

Vec3d Vec3d::Transformed(const Trsf3d &theTrsf) const {
  Vec3d aVec(myXYZ);
  return aVec.Transform(theTrsf) ? aVec : Unset();
}

Naive_Bool Vec3d::Dump(Naive_Vector3d_t &theVec) const {
  if (!IsValid())
    return Naive_False;
  theVec.x = X();
  theVec.y = Y();
  theVec.z = Z();
  return Naive_True;
}

const Vec3d operator+(const Vec3d &theVec1, const Vec3d &theVec2) {
  return theVec1.Added(theVec2);
}

const Vec3d operator-(const Vec3d &theVec1, const Vec3d &theVec2) {
  return theVec1.Subtracted(theVec2);
}

const Vec3d operator-(const Vec3d &theVec) { return theVec.Negated(); }

const Vec3d operator*(const Vec3d &theVec, const Naive_Real theT) {
  return theVec.Multiplied(theT);
}

const Vec3d operator*(const Naive_Real theT, const Vec3d &theVec) {
  return theVec.Multiplied(theT);
}

const Naive_Real operator*(const Vec3d theVec1, const Vec3d &theVec2) {
  return theVec1.Dot(theVec2);
}

const Vec3d operator/(const Vec3d &theVec, const Naive_Real theT) {
  return theVec.Divided(theT);
}

Naive_NAMESPACE_END(math);
