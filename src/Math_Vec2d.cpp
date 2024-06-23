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
