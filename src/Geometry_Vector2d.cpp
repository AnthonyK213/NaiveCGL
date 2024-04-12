#include <naivecgl/Geometry/Vector2d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Vector2d::Vector2d()
    : myXY(math::Constant::UnsetValue(), math::Constant::UnsetValue()) {}

Vector2d::Vector2d(const Naive_Real theX, const Naive_Real theY)
    : myXY(theX, theY) {}

Vector2d::Vector2d(const Naive_Vector2d_T &theVec) : myXY(theVec.x, theVec.y) {}

Vector2d::Vector2d(const Naive_XY &theXY) : myXY(theXY) {}

Naive_Bool Vector2d::IsValid() const {
  return math::Util::IsValidDouble(X()) && math::Util::IsValidDouble(Y());
}

const Vector2d &Vector2d::Unset() {
  static Vector2d p{};
  return p;
}

Naive_Bool Vector2d::Dump(Naive_Vector2d_T &theV) const {
  if (!IsValid())
    return false;

  theV.x = X();
  theV.y = Y();
  return true;
}

Naive_NAMESPACE_END(geometry);
