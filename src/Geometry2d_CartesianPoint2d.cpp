#include <naivecgl/Geometry2d/CartesianPoint2d.h>
#include <naivecgl/Math/Constant.h>
#include <naivecgl/Math/Util.h>

Naive_NAMESPACE_BEGIN(geometry2d);

Naive_IMPLEMENT_RTTI(CartesianPoint2d);

CartesianPoint2d::CartesianPoint2d() : myPnt2d() {}

CartesianPoint2d::CartesianPoint2d(const Naive_Real theX, const Naive_Real theY)
    : myPnt2d(theX, theY) {}

CartesianPoint2d::CartesianPoint2d(const Naive_Pnt2d &thePnt2d)
    : myPnt2d(thePnt2d) {}

Naive_Bool CartesianPoint2d::IsValid() const { return myPnt2d.IsValid(); }

Handle_Naive_Geometry2d CartesianPoint2d::Clone() const {
  return new CartesianPoint2d(myPnt2d);
}

Naive_NAMESPACE_END(geometry2d);
