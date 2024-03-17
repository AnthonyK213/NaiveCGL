#include <naivecgl/Geometry/Point2d.h>
#include <naivecgl/Math/Constants.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry);

Point2d::Point2d() : myXY(math::UnsetValue, math::UnsetValue) {}

Point2d::Point2d(const Naive_Real theX, const Naive_Real theY)
    : myXY(theX, theY) {}

Point2d::Point2d(const Naive_Point2d_T &thePoint)
    : myXY(thePoint.x, thePoint.y) {}

Point2d::Point2d(const Naive_XY &theXY) : myXY(theXY) {}

Naive_Bool Point2d::IsValid() const {
  return math::IsValidDouble(X()) && math::IsValidDouble(Y());
}

Naive_Real Point2d::DistanceTo(const Point2d &theP) const {
  if (!IsValid())
    return math::UnsetValue;
  return (myXY - theP.myXY).norm();
}

Naive_Real Point2d::DistanceToSquared(const Point2d &theP) const {
  if (!IsValid())
    return math::UnsetValue;
  return (myXY - theP.myXY).squaredNorm();
}

const Point2d &Point2d::Unset() {
  static Point2d p{};
  return p;
}

Naive_Bool Point2d::Dump(Naive_Point2d_T &theP) const {
  if (!IsValid())
    return false;

  theP.x = X();
  theP.y = Y();
  return true;
}

Naive_NAMESPACE_END(geometry);
