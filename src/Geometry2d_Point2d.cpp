#include <naivecgl/Geometry2d/Point2d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry2d);

Naive_IMPLEMENT_RTTI(Point2d);

Point2d::Point2d() : myPnt2d() {}

Point2d::Point2d(const Naive_Real theX, const Naive_Real theY)
    : myPnt2d(theX, theY) {}

Point2d::Point2d(const Naive_Pnt2d &thePnt2d)
    : myPnt2d(thePnt2d.X(), thePnt2d.Y()) {}

Naive_Real Point2d::DistanceTo(const Naive_Handle<Point2d> &theP) const {
  if (theP.IsNull())
    return math::Constant::UnsetReal();
  return myPnt2d.DistanceTo(theP->myPnt2d);
}

Naive_Real Point2d::DistanceToSquared(const Naive_Handle<Point2d> &theP) const {
  if (theP.IsNull())
    return math::Constant::UnsetReal();
  return myPnt2d.DistanceToSquared(theP->myPnt2d);
}

Naive_Bool Point2d::IsValid() const { return myPnt2d.IsValid(); }

Handle_Naive_Geometry2d Point2d::Clone() const { return new Point2d(myPnt2d); }

Naive_NAMESPACE_END(geometry2d);
