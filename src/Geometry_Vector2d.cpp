﻿#include <naivecgl/Geometry/Vector2d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Vector2d::Vector2d()
    : myXY(math::Constant::UnsetReal(), math::Constant::UnsetReal()) {}

Vector2d::Vector2d(const Naive_Real theX, const Naive_Real theY)
    : myXY(theX, theY) {}

Vector2d::Vector2d(const Naive_Vector2d_t &theVec) : myXY(theVec.x, theVec.y) {}

Vector2d::Vector2d(const Naive_XY &theXY) : myXY(theXY) {}

Naive_Bool Vector2d::IsValid() const {
  return math::Util::IsValidReal(X()) && math::Util::IsValidReal(Y());
}

const Vector2d &Vector2d::Unset() {
  static Vector2d p{};
  return p;
}

Naive_Bool Vector2d::Dump(Naive_Vector2d_t &theV) const {
  if (!IsValid())
    return Naive_False;

  theV.x = X();
  theV.y = Y();
  return Naive_True;
}

Naive_NAMESPACE_END(geometry);
