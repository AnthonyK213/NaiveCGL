#include <naivecgl/Geometry2d/Point2d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry2d);

Naive_IMPLEMENT_RTTI(Point2d);

Naive_Real Point2d::DistanceTo(const Naive_Handle<Point2d> &theP) const {
  return ::std::sqrt(DistanceToSquared(theP));
}

Naive_Real Point2d::DistanceToSquared(const Naive_Handle<Point2d> &theP) const {
  Naive_Real dX = X() - theP->X();
  Naive_Real dY = Y() - theP->Y();
  return dX * dX + dY * dY;
}

Naive_NAMESPACE_END(geometry2d);
