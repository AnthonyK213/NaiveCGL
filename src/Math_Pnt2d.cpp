#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Pnt2d.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(math);

Pnt2d::Pnt2d() : myXY(Constant::UnsetReal(), Constant::UnsetReal()) {}

Pnt2d::Pnt2d(const Naive_Real theX, const Naive_Real theY) : myXY(theX, theY) {}

Pnt2d::Pnt2d(const Naive_Point2d_t &thePnt) : myXY(thePnt.x, thePnt.y) {}

Pnt2d::Pnt2d(const Naive_XY &theXY) : myXY(theXY) {}

Naive_Bool Pnt2d::IsValid() const {
  return Util::IsValidReal(X()) && Util::IsValidReal(Y());
}

Naive_Real Pnt2d::DistanceTo(const Pnt2d &theP) const {
  if (!IsValid())
    return Constant::UnsetReal();
  return (myXY - theP.myXY).norm();
}

Naive_Real Pnt2d::DistanceToSquared(const Pnt2d &theP) const {
  if (!IsValid())
    return Constant::UnsetReal();
  return (myXY - theP.myXY).squaredNorm();
}

const Pnt2d &Pnt2d::Unset() {
  static Pnt2d p{};
  return p;
}

Naive_Bool Pnt2d::Dump(Naive_Point2d_t &theP) const {
  if (!IsValid())
    return Naive_False;

  theP.x = X();
  theP.y = Y();
  return Naive_True;
}

Naive_NAMESPACE_END(math);
