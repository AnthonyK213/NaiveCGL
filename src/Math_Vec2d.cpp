#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Util.h>
#include <naivecgl/Math/Vec2d.h>

Naive_NAMESPACE_BEGIN(math);

Vec2d::Vec2d() : myXY(Constant::UnsetReal(), Constant::UnsetReal()) {}

Vec2d::Vec2d(const Naive_Real theX, const Naive_Real theY) : myXY(theX, theY) {}

Vec2d::Vec2d(const Naive_Vec2d_t &theVec) : myXY(theVec.x, theVec.y) {}

Vec2d::Vec2d(const Naive_XY &theXY) : myXY(theXY) {}

Naive_Bool Vec2d::IsValid() const {
  return Util::IsValidReal(X()) && Util::IsValidReal(Y());
}

Naive_Bool Vec2d::IsZero() const { return myXY.isZero(Precision::Epsilon0()); }

Naive_Real Vec2d::Length() const { return myXY.norm(); }

Naive_Real Vec2d::SquareLength() const { return myXY.squaredNorm(); }

const Vec2d &Vec2d::XAxis() {
  static Vec2d X{1., 0.};
  return X;
}

const Vec2d &Vec2d::YAxis() {
  static Vec2d Y{0., 1.};
  return Y;
}

const Vec2d &Vec2d::Zero() {
  static Vec2d Z{0., 0.};
  return Z;
}

const Vec2d &Vec2d::Unset() {
  static Vec2d p{};
  return p;
}

Naive_Bool Vec2d::Normalize() {
  if (IsValid() && !IsZero()) {
    myXY.normalize();
    return Naive_True;
  }
  return Naive_False;
}

Vec2d Vec2d::Normalized() const {
  Vec2d aV(*this);
  if (aV.Normalize())
    return aV;
  return Unset();
}

void Vec2d::Add(const Vec2d &theVec) { myXY += theVec.myXY; }

Vec2d Vec2d::Added(const Vec2d &theVec) const { return {myXY + theVec.myXY}; }

void Vec2d::Subtract(const Vec2d &theVec) { myXY -= theVec.myXY; }

Vec2d Vec2d::Subtracted(const Vec2d &theVec) const {
  return {myXY - theVec.myXY};
}

void Vec2d::Multiply(const Naive_Real theT) { myXY *= theT; }

Vec2d Vec2d::Multiplied(const Naive_Real theT) const { return {myXY * theT}; }

Naive_Bool Vec2d::Divide(const Naive_Real theT) {
  if (Util::EpsilonEquals(theT, 0.0))
    return Naive_False;
  myXY /= theT;
  return Naive_True;
}

Vec2d Vec2d::Divided(const Naive_Real theT) const {
  Vec2d aVec(*this);
  return aVec.Divide(theT) ? aVec : Unset();
}

Naive_Real Vec2d::Dot(const Vec2d &theV) const {
  if (IsValid() && theV.IsValid())
    return myXY.dot(theV.myXY);
  return Constant::UnsetReal();
}

Naive_Real Vec2d::Crossed(const Vec2d &theV) const {
  if (IsValid() && theV.IsValid())
    return X() * theV.Y() - theV.X() * Y();
  return Constant::UnsetReal();
}

Naive_XYZ Vec2d::HomoCoord() const { return Naive_XYZ{myXY.x(), myXY.y(), 0.}; }

Naive_Bool Vec2d::Dump(Naive_Vec2d_t &theV) const {
  if (!IsValid())
    return Naive_False;

  theV.x = X();
  theV.y = Y();
  return Naive_True;
}

Naive_NAMESPACE_END(math);
