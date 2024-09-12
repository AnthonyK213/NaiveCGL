#include <naivecgl/Math/Constant.h>
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

Vec3d::Vec3d(const Naive_Vec3d_t &theVec)
    : myXYZ(theVec.x, theVec.y, theVec.z) {}

Naive_Bool Vec3d::IsValid() const {
  return Util::IsValidReal(X()) && Util::IsValidReal(Y()) &&
         Util::IsValidReal(Z());
}

Naive_Bool Vec3d::IsUnitVector() const {
  return ::std::abs(Length() - 1.) <= Precision::Zero();
}

Naive_Bool Vec3d::IsZero() const { return myXYZ.isZero(Precision::Zero()); }

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

void Vec3d::Add(const Vec3d &theVec) { myXYZ += theVec.myXYZ; }

Vec3d Vec3d::Added(const Vec3d &theVec) const { return {myXYZ + theVec.myXYZ}; }

void Vec3d::Subtract(const Vec3d &theVec) { myXYZ -= theVec.myXYZ; }

Vec3d Vec3d::Subtracted(const Vec3d &theVec) const {
  return {myXYZ - theVec.myXYZ};
}

void Vec3d::Multiply(const Naive_Real theT) { myXYZ *= theT; }

Vec3d Vec3d::Multiplied(const Naive_Real theT) const { return {myXYZ * theT}; }

Naive_Bool Vec3d::Divide(const Naive_Real theT) {
  if (Util::EpsilonEquals(theT, 0.0))
    return Naive_False;
  myXYZ /= theT;
  return Naive_True;
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

void Vec3d::Cross(const Vec3d &theVec) { myXYZ = myXYZ.cross(theVec.myXYZ); }

Vec3d Vec3d::Crossed(const Vec3d &theVec) const {
  return myXYZ.cross(theVec.myXYZ);
}

Naive_Bool Vec3d::EpsilonEquals(const Vec3d &theVec, const Naive_Real theE) {
  return Util::EpsilonEquals(X(), theVec.X(), theE) &&
         Util::EpsilonEquals(Y(), theVec.Y(), theE) &&
         Util::EpsilonEquals(Z(), theVec.Z(), theE);
}

void Vec3d::Reverse() { Negate(); }

Naive_Bool Vec3d::Equals(const Vec3d &theVec) { return myXYZ == theVec.myXYZ; }

void Vec3d::Transform(const Trsf3d &theTrsf) {
  if (!theTrsf.IsIdentity())
    myXYZ = theTrsf.Affine().rotation() * myXYZ;
}

Vec3d Vec3d::Transformed(const Trsf3d &theTrsf) const {
  Vec3d aVec(myXYZ);
  aVec.Transform(theTrsf);
  return aVec;
}

Naive_XYZW Vec3d::HomoCoord() const {
  return Naive_XYZW{myXYZ.x(), myXYZ.y(), myXYZ.z(), 0.};
}

Naive_Bool Vec3d::HomoCoord(const Naive_XYZW &theXYZW) {
  myXYZ = theXYZW.head<3>();
  if (!Util::EpsilonEquals(theXYZW.w(), 0.)) {
    myXYZ /= theXYZW(3);
  }

  return Naive_True;
}

Naive_Bool Vec3d::Dump(Naive_Vec3d_t &theVec) const {
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
