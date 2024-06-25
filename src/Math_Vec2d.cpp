#include <naivecgl/Math/Util.h>
#include <naivecgl/Math/Vec2d.h>

Naive_NAMESPACE_BEGIN(math);

Vec2d::Vec2d() : myXY(Constant::UnsetReal(), Constant::UnsetReal()) {}

Vec2d::Vec2d(const Naive_Real theX, const Naive_Real theY) : myXY(theX, theY) {}

Vec2d::Vec2d(const Naive_Vector2d_t &theVec) : myXY(theVec.x, theVec.y) {}

Vec2d::Vec2d(const Naive_XY &theXY) : myXY(theXY) {}

Naive_Bool Vec2d::IsValid() const {
  return Util::IsValidReal(X()) && Util::IsValidReal(Y());
}

Naive_Bool Vec2d::IsZero() const {
  return myXY.isZero(Constant::ZeroTolerance());
}

Naive_Bool Vec2d::Normalize() {
  if (IsValid() && !IsZero()) {
    myXY.normalize();
    return Naive_True;
  }
  return Naive_False;
}

Naive_EXPORT Vec2d Vec2d::Normalized() const {
  Vec2d aV(*this);
  if (aV.Normalize())
    return aV;
  return Unset();
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

const Vec2d &Vec2d::Unset() {
  static Vec2d p{};
  return p;
}

Naive_Bool Vec2d::Dump(Naive_Vector2d_t &theV) const {
  if (!IsValid())
    return Naive_False;

  theV.x = X();
  theV.y = Y();
  return Naive_True;
}

Naive_NAMESPACE_END(math);
